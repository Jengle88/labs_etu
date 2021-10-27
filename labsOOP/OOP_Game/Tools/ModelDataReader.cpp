#include "ModelDataReader.h"


std::string & ModelDataReader::stripStr(std::string &str) {
    int rightIndex = str.size() - 1;
    while (std::isspace(str[rightIndex]) && rightIndex - 1 >= 0)
        rightIndex--; // ищем первый не пробельный символ
    int leftIndex = 0;
    int trueLeftIndex = 0;
    while (std::isspace(str[leftIndex]) && leftIndex < rightIndex) {
        leftIndex++;
    }
    while (leftIndex <= rightIndex) {
        str[trueLeftIndex++] = str[leftIndex++];
    }
    str.resize(trueLeftIndex);
    return str;
}

std::string ModelDataReader::readXMLStripStr(std::istream &input, const std::string& startTags) {
    std::string str;
    getline(input, str); // считываем начальный заголовок
    if (stripStr(str) == startTags) {
        getline(input, str); // считываем название
        stripStr(str);
        std::string temp;
        getline(input, temp); // считываем конечный заголовок
//        int z = 2;
    }
    return str;
}

std::vector<std::string> ModelDataReader::readXMLModelDataInLines(std::istream &input, int countLine) {
    std::string title;
    getline(input, title); // считываем заголовок
    std::vector<std::string> modelData(countLine);
    for (int i = 0; i < countLine; ++i) {
        getline(input, modelData[i]);
        modelData[i].pop_back();
    }
    getline(input, title); // считываем заголовок
    return modelData;
}

std::pair<std::string, std::vector<std::string>> ModelDataReader::readXMLModelEnemy(std::istream &input) {
    std::string name = readXMLStripStr(input, xmlTags.namePartStartTag);
    auto data = readXMLModelDataInLines(input, modelHeight);
    return {name, data};
}

std::vector<std::pair<std::string, std::vector<std::string>>> ModelDataReader::readXMLModelHeroData(std::istream &input) {
    int countModels = std::stoi(readXMLStripStr(input, xmlTags.countModelsStartTag));
    std::vector<std::pair<std::string, std::vector<std::string>>> data(countModels);
    for (int i = 0; i < countModels; ++i) {
        auto name = readXMLStripStr(input, xmlTags.namePartStartTag);
        std::vector<std::string> lines;
        if (name.find("head") != std::string::npos) {
            lines = readXMLModelDataInLines(input, modelHeadHeight);
        } else if (name.find("body") != std::string::npos) {
            lines = readXMLModelDataInLines(input, modelBodyHeight);
        } else if (name.find("legs") != std::string::npos) {
            lines = readXMLModelDataInLines(input, modelLegsHeight);
        }
        data[i].second.reserve(lines.size() + 1);
        for (auto & line : lines) {
            data[i].second.push_back(line);
        }
        data[i].first = name;
    }
    return data;
}

std::vector<std::pair<std::string, std::vector<std::string>>> ModelDataReader::readXMLModelData(const std::string nameFile) {
    std::vector<std::pair<std::string, std::vector<std::string>>> data;
    std::fstream input(nameFile, std::ios_base::in);
    std::string str;
    getline(input, str);
    if (stripStr(str) == xmlTags.objectsStartTag) {
        int countModels = std::stoi(readXMLStripStr(input, xmlTags.countModelsStartTag));
        data.reserve(countModels);
        for (int i = 0; i < countModels; ++i) {
            data.push_back(readXMLModelEnemy(input));
        }
        auto heroData = readXMLModelHeroData(input);
        data.reserve(data.size() + heroData.size());
        for (auto & heroModel : heroData) {
            data.push_back(heroModel);
        }
    }
    return data;
}

