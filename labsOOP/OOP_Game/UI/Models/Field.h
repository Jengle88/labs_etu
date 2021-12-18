#pragma once
#include "../../Tools/Grid.h"
#include "../../Tools/FieldIterator.h"
#include "../../Characters/MainHero.h"
#include "../../Characters/Enemy.h"
#include "../../Characters/Monster.h"
#include "../../Characters/Archer.h"
#include "../../Characters/Gargoyle.h"
#include "../../Data/DataManager.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <map>

#define PERCENT_WALLS 35

class Field {
	Grid field;
    CellPoint start;
	CellPoint finish;
    CellPoint heroPos;
    MainHero hero;
    DataManager *dataManager;
    std::map<CellPoint, Enemy*> enemies;
    int maxCntEnemy;
    int timeBetweenGenerateEnemy;
    bool wayGenerated = false;
    bool wallsGenerated = false;
    bool chosenStartFinish = false;
    int countWalls = 0;
    int distStartFinish = 2;
    long int counterSteps = 0;
    bool isCorrectStartFinish(CellPoint start, CellPoint finish) const;
    bool isCorrectDistStartFinish(CellPoint start, CellPoint finish) const;

    CellPoint generateBorderPoint() const;
    void generateStartFinishWay();
    void generateWayWithoutWalls(CellPoint start, CellPoint finish);
    void generateWalls(int countWalls);

    void createMonster();
    void createArcher();
    void createGargoyle();
public:
    Field(int height, int width, DataManager *dataManager, CellPoint start = CellPoint(0,0), CellPoint finish = CellPoint(0,0), Grid grid = Grid());
    Field(const Field& field);
    Field& operator=(const Field& field);
    Field(Field && field);
    Field& operator=(Field&& field);
    ~Field();

    std::vector<std::string>
    prepareDataToSave(bool sizeOfField, bool startFinishPos, bool posOfWalls, bool posOfCharacters, bool cntSteps,
                      bool heroInfo) const;

    // Генераторы
    bool generateFullField(int countWalls);
    void createHero();
    void createRandomEnemy(); // Паттерн: Фабрика
    CellPoint generateRandomFreePoint();

    // Передвижение персонажей
    bool moveHero(CellPoint to);
    void moveEnemy(CellPoint from, CellPoint to);
    void moveEnemies();
    void killEnemy(CellPoint from);

    // Геттеры / Сеттеры
    Cell getElem(CellPoint point) const;
    void setElem(CellPoint point, CellObject object);
    int getHeight() const;
    int getWidth() const;
    bool getStatusWay() const;
    bool getStatusWalls() const;
    bool getStatusStartFinish() const;
    FieldIterator getFieldIterator();
    CellPoint getHeroPos() const;
    void setHeroOnStart();
    MainHero& getHero();
    Enemy& getEnemyFromPoint(CellPoint point);
    std::map<CellPoint, Enemy *> &getEnemies();
    const Grid &getGrid() const;
    void setRules(int maxCntEnemy, int timeBetweenGenerateEnemy);

    void incCountSteps();
    long getCountSteps() const;

    friend class FieldScreen; // т.к FieldScreen использует проверку данных
};











