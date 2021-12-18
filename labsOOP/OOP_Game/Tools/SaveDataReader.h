#pragma once

#include <string>
#include <fstream>
#include "SaveDataAdapter.h"

class SaveDataReader {
    std::vector<std::string> splitLine(const std::string &line);
    void dataValidator(const SaveDataAdapter& dataAdapter);
    static bool tagValidator(std::fstream &in);
    static std::vector<std::string> extractUsefulInformation(std::fstream& in);
    static void nextPosition(const std::vector<std::string> &info, int &posInInfo) ;
    bool readInfo(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info,
                  int &posInInfo);
public:
    static const std::string START_TAG;
    static const std::string END_TAG;
    void readSaveFile(const std::string& pathToFile, SaveDataAdapter& saveDataAdapter);

    void readWallsPos(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info, int &posInInfo,
                      std::vector<std::string> &tokens);

    void readEnemiesPosHealth(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info, int &posInInfo,
                              std::vector<std::string> &tokens);

    void readThingsPosLevel(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info, int &posInInfo,
                            std::vector<std::string> &tokens);

    void readHeroThings(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info, int &posInInfo,
                        std::vector<std::string> &tokens);

    void readHeroAchievement(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info, int &posInInfo,
                             std::vector<std::string> &tokens);
};


