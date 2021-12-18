#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <memory>
#include "../UI/LoadScreen.h"

class SaveManager {
    static std::unique_ptr<SaveManager> instance;
    std::string pathToSaveDirectory;
    std::vector<std::string> pathsToFiles;
    std::vector<std::string> namesOfFiles;
    std::vector<std::string> loadPathsToFiles() const;
    std::vector<std::string> extractNamesOfFiles(std::vector<std::string> &pathsToFiles) const;
    explicit SaveManager(const std::string &pathToDirectory);
public:
    static std::unique_ptr<SaveManager>* getInstance(const std::string& pathToDirectory);
    void reloadPathsToFiles(const std::string &pathToDirectory);
    const std::vector<std::string>& getNamesOfFiles() const;
    int deleteFile(int pos);
    bool saveData(const std::vector<std::string> &data) const;
};


