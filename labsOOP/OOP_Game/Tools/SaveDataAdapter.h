#pragma once

#include <vector>
#include "CellPoint.h"

class SaveDataAdapter {
    int heightField = -1, widthField = -1;
    CellPoint start = {-1, -1}, finish = {-1, -1};
    std::vector<CellPoint> walls;
    CellPoint heroPos = {-1, -1};
    double heroHealth = -1;
    std::vector<std::pair<std::string, std::pair<double, CellPoint>>> enemiesPos;
    int cntSteps = -1;
    std::vector<std::pair<std::string, std::pair<int, CellPoint>>> thingsPos;
    int heroLevel = -1;
    std::vector<std::pair<std::string, int>> heroThings;
    std::vector<std::pair<std::string, int>> heroAchievements;
public:
    SaveDataAdapter() = default;
    int getHeightField() const;
    int getWidthField() const;
    const CellPoint &getStart() const;
    const CellPoint &getFinish() const;
    const std::vector<CellPoint> &getWalls() const;
    const CellPoint &getHeroPos() const;
    double getHeroHealth() const;
    const std::vector<std::pair<std::string, std::pair<double, CellPoint>>> &getEnemiesPos() const;
    int getCntSteps() const;
    const std::vector<std::pair<std::string, std::pair<int, CellPoint>>> &getThingsPos() const;
    int getHeroLevel() const;
    const std::vector<std::pair<std::string, int>> &getHeroThings() const;
    const std::vector<std::pair<std::string, int>> &getHeroAchievements() const;
    void setHeightField(int heightField);
    void setWidthField(int widthField);
    void setStart(const CellPoint &start);
    void setFinish(const CellPoint &finish);
    void setWalls(const std::vector<CellPoint> &walls);
    void setHeroPos(const CellPoint &heroPos);
    void setHeroHealth(double heroHealth);
    void setEnemiesPos(const std::vector<std::pair<std::string, std::pair<double, CellPoint>>> &enemiesPos);
    void setCntSteps(int cntSteps);
    void setThingsPos(const std::vector<std::pair<std::string, std::pair<int, CellPoint>>> &thingsPos);
    void setHeroLevel(int levelOfThings);
    void setHeroThings(const std::vector<std::pair<std::string, int>> &heroThings);
    void setHeroAchievements(const std::vector<std::pair<std::string, int>> &heroAchievements);
};


