#pragma once
#include "../../Tools/Grid.h"
#include "../../Tools/FieldIterator.h"
#include "../../Entity/Characters/MainHero.h"
#include "../../Entity/Characters/Enemy.h"
#include "../../Entity/Characters/Monster.h"
#include "../../Entity/Characters/Archer.h"
#include "../../Entity/Characters/Gargoyle.h"
#include "../../Data/DataManager.h"
#include "../../Tools/SaveDataAdapter.h"
#include "FieldBuilder.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>


class Field {
	Grid grid;
    FieldBuilder *builder;
    CellPoint start;
	CellPoint finish;
    CellPoint heroPos;
    MainHero hero;
    std::shared_ptr<DataManager> dataManager;
    std::map<CellPoint, Enemy*> enemies;
    int maxCntEnemy;
    int timeBetweenGenerateEnemy;
    long int counterSteps = 0;

    void createMonster(CellPoint monsterStartPoint);
    void createMonster();
    void createArcher(CellPoint archerStartPoint);
    void createArcher();
    void createGargoyle(CellPoint gargoyleStartPoint);
    void createGargoyle();
public:
    Field(int height, int width, std::shared_ptr<DataManager> dataManager, FieldBuilder *builder,
          CellPoint start = CellPoint(0, 0), CellPoint finish = CellPoint(0, 0), Grid grid = Grid());
    Field(std::shared_ptr<DataManager> dataManager, FieldBuilder *builder);
    Field(const Field& field);
    Field& operator=(const Field& field);
    Field(Field && field);
    Field& operator=(Field&& field);
    ~Field();

    std::vector<std::string>
    prepareDataToSave(bool sizeOfField, bool startFinishPos, bool posOfWalls, bool posOfCharacters, bool cntSteps,
                      bool heroInfo) const;
    void rebuildField(const SaveDataAdapter& adapter);

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
    FieldIterator getFieldIterator();
    CellPoint getHeroPos() const;
    const std::shared_ptr<DataManager> & getDataManager() const;
    void setHeroOnStart();
    MainHero& getHero();
    Enemy& getEnemyFromPoint(CellPoint point);
    std::map<CellPoint, Enemy *> &getEnemies();
    const Grid &getGrid() const;
    void setRules(int maxCntEnemy, int timeBetweenGenerateEnemy);

    void incCountSteps();
    long getCountSteps() const;

    friend class FieldScreen; // т.к FieldScreen использует проверку данных
    friend class FieldBuilder;
};












