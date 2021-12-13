#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

class KeyboardDataReader {
    static std::string startTag;
    static std::string endTag;
    static std::vector<std::string> readLine(std::fstream& input);
public:
    static std::unordered_map<std::string, std::unordered_map<std::string, char>> readKeyboardSetting(const std::string& nameFile);
};


