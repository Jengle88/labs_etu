#include <iostream>
#include <vector>

bool checkSubstr(const std::string &dist, const std::string &src, int posStart) {
    int srcIndex = 0;
    for (int i = posStart; i < dist.size() && srcIndex < src.size(); ++i) {
        if (dist[i] != src[srcIndex++])
            return false;
    }
    return srcIndex == src.size();
}

std::vector<int> solve(const std::string &pattern, const std::string &text) {

    const int xValue = 7;
    const long long pModule = 1e8 + 7;
    std::vector<int> xPowValues(pattern.size());
    std::vector<int> hashTextValues(text.size(), 0);
    xPowValues[0] = 1;
    for (int i = 1; i < xPowValues.size(); ++i) {
        xPowValues[i] = ((long long)xPowValues[i-1] * xValue) % pModule;
    }

    for (int i = text.size()- pattern.size(); i < text.size(); i++) {
        hashTextValues[text.size() - pattern.size()] = (((long long)text[i] * xPowValues[i - (text.size() - pattern.size())]) % pModule + hashTextValues[text.size() - pattern.size()]) % pModule;
    }
    for (int i = text.size() - 1 - pattern.size(); i >= 0; i--) {
        hashTextValues[i] = ((((hashTextValues[i + 1] - ((long long)text[i + pattern.size()] * xPowValues[pattern.size() - 1]) % pModule + pModule) % pModule) * xValue) % pModule + ((long long)text[i] * xPowValues[0]) % pModule) % pModule;
    }
    int hashPattern = 0;
    for (int i = 0 ; i < pattern.size(); ++i) {
        hashPattern = (((long long)pattern[i] * xPowValues[i]) % pModule + hashPattern) % pModule;
    }

    std::vector<int> resultPos;
    for (int i = 0; i < text.size() - pattern.size() + 1; ++i) {
        if (hashTextValues[i] == hashPattern && checkSubstr(text, pattern, i))
            resultPos.push_back(i);
    }

    return resultPos;
}