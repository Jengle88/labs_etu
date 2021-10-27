#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>

class ModelDataReader {
    struct XMLObjectsTags {
    public:
        const std::string objectsStartTag = "<objects>";
        const std::string objectsEndTag = "</objects>";
        const std::string namePartStartTag = "<namePart>";
        const std::string namePartEndTag = "</namePart>";
        const std::string drawPartStartTag = "<drawPart>";
        const std::string drawPartEndTag = "</drawPart>";
        const std::string countModelsStartTag = "<countModels>";
        const std::string countModelsEndTag = "</countModels>";
    } xmlTags;
    const int modelHeight = 9;
    const int modelHeadHeight = 3;
    const int modelBodyHeight = 4;
    const int modelLegsHeight = 2;
    const std::set<std::string> enemyNames = {"Monster", "Archer", "Gargoyle"};
    std::string & stripStr(std::string &str);
    std::vector<std::string> readXMLModelDataInLines(std::istream &input, int countLine);
    std::string readXMLStripStr(std::istream &input, const std::string& startTags);
    std::pair<std::string, std::vector<std::string>> readXMLModelEnemy(std::istream &input); // имя + модель
    std::vector<std::pair<std::string, std::vector<std::string>>> readXMLModelHeroData(std::istream &input);// массив {имя, модель}
public:
    std::vector<std::pair<std::string, std::vector<std::string>>> readXMLModelData(const std::string nameFile); //  массив {имя, модель}

};
