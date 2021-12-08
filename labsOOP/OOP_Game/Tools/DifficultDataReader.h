#pragma once
#include <vector>
#include <unordered_map>
#include "../Rules/CharacterProperties.h"
#include "../Rules/ThingProperties.h"
#include "../Rules/DifficultPreset.h"

class DifficultDataReader {
    static std::string startTag;
    static std::string endTag;
    static const std::unordered_map<std::string, int> strToTypeObject;
    static std::vector<std::string> readLine(std::fstream& input);
    static std::vector<std::unordered_map<std::string, std::string>> readSetData(std::fstream& input);
    static std::unordered_map<std::string, CharacterProperties> readCharactersParams(std::fstream& input);
    static std::unordered_map<std::string, ThingProperties> readThingsProperties(std::fstream& input);
    static std::unordered_map<std::string, int> readCntKilledEnemies(std::fstream& input);
    static DifficultPreset readRule(std::fstream& input);
public:
    static std::unordered_map<std::string, DifficultPreset> readRulesPresets(const std::string& nameFile);

};

