#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

class KeyDataReader {
    static const std::string START_TAG;
    static const std::string END_TAG;
    static std::vector<std::string> readLine(std::fstream& input);
public:
    static std::unordered_map<std::string, std::unordered_map<std::string, char>> readKeysSettings(const std::string& nameFile);
};
