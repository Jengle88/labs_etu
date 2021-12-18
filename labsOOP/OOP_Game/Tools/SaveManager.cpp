#include "SaveManager.h"
#include "SaveDataReader.h"
#include "../Logger/LoggerPull.h"

std::unique_ptr<SaveManager> SaveManager::instance = nullptr;

SaveManager::SaveManager(const std::string &pathToDirectory) {
    pathToSaveDirectory = pathToDirectory;
    pathsToFiles = loadPathsToFiles();
    namesOfFiles = extractNamesOfFiles(pathsToFiles);
}

std::vector<std::string> SaveManager::loadPathsToFiles() const {
    namespace fs = std::filesystem;
    std::vector<std::string> pathToFiles;
    for(const auto& pathToFile : fs::directory_iterator(pathToSaveDirectory)) {
        pathToFiles.push_back(pathToFile.path());
    }
    std::sort(pathToFiles.rbegin(), pathToFiles.rend());
    return pathToFiles;
}

std::vector<std::string>
SaveManager::extractNamesOfFiles(std::vector<std::string> &pathsToFiles) const {
    std::vector<std::string> nameFiles;
    nameFiles.reserve(pathsToFiles.size());
    for (auto pathToFile: pathsToFiles) {
        nameFiles.push_back(pathToFile.erase(0, pathToSaveDirectory.size()));
    }
    return nameFiles;
}

std::unique_ptr<SaveManager>* SaveManager::getInstance(const std::string &pathToDirectory) {
    if (instance == nullptr)
        instance = std::unique_ptr<SaveManager>(new SaveManager(pathToDirectory)); // нельзя использовать make_unique, т.к конструктор приватный
    return &instance;
}

void SaveManager::reloadPathsToFiles(const std::string &pathToDirectory) {
    pathToSaveDirectory = pathToDirectory;
    pathsToFiles = loadPathsToFiles();
    namesOfFiles = extractNamesOfFiles(pathsToFiles);
}

const std::vector<std::string> &SaveManager::getNamesOfFiles() const {
    return namesOfFiles;
}

int SaveManager::deleteFile(int pos) {
    namespace fs = std::filesystem;
    if (0 <= pos && pos < pathsToFiles.size()) {
        int answer = fs::remove(pathsToFiles[pos]); // возвращает true, если удалил, или false, если нет
        pathsToFiles.erase(pathsToFiles.begin() + pos);
        namesOfFiles.erase(namesOfFiles.begin() + pos);
        return answer;
    }
    return FileRemoveState::FILE_NOT_FOUND;
}

bool SaveManager::saveData(const std::vector<std::string> &data) const {
    time_t seconds = time(nullptr);
    tm* timeinfo = localtime(&seconds);
    std::string nameOfFile = "../SaveData/Save_" + std::to_string(timeinfo->tm_year + 1900) + "_" +std::to_string(timeinfo->tm_mon + 1)
            + "_" +std::to_string(timeinfo->tm_mday) + "_" + std::to_string(timeinfo->tm_hour)
            + "_" +std::to_string(timeinfo->tm_min) + "_" +std::to_string(timeinfo->tm_sec) + ".txt";
    std::fstream out(nameOfFile, std::ios_base::out);
    if (!out.is_open())
        return false;
    for (const auto &item: data) {
        out << item;
    }
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Данные успешно сохранены в файл " + nameOfFile));
    out.close();
    return true;
}

SaveDataAdapter SaveManager::loadData(int selectedFile, bool &check) const {
    SaveDataReader dataReader;
    SaveDataAdapter adapter;
    check = true;
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Начато считывание файла загрузки " + pathsToFiles[selectedFile] ));
    try {
        dataReader.readSaveFile(pathsToFiles[selectedFile], adapter);
    } catch (std::exception& e) {
        check = false;
        LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>(e.what()));
    }
    return adapter;
}


