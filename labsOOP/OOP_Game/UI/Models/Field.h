#pragma once
#include "../../Tools/Grid.h"
#include "../../Tools/FieldIterator.h"
#include "../../Characters/MainHero.h"
#include "../../Characters/Enemy.h"
#include "../../Characters/Monster.h"
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
    std::map<CellPoint, Enemy*> enemies;
    bool wayGenerated = false;
    bool wallsGenerated = false;
    bool chosenStartFinish = false;
    int countWalls = 0;
    int distStartFinish = 2;
    bool isCorrectStartFinish(CellPoint start, CellPoint finish) const;
    bool isCorrectDistStartFinish(CellPoint start, CellPoint finish) const;
    CellPoint generateBorderPoint() const;
    void generateStartFinishWay();
    void generateWayWithoutWalls(CellPoint start, CellPoint finish);
    void generateWalls(int countWalls);
public:
    Field();
    Field(int height, int width, CellPoint start = CellPoint(0,0), CellPoint finish = CellPoint(0,0), Grid grid = Grid());
    Field(const Field& field);
    Field& operator=(const Field& field);
    Field(Field && field);
    Field& operator=(Field&& field);
    ~Field();
    // Генераторы
    bool generateFullField(int countWalls);
    void createHero(double health, double attackPower, double protection, double luck);
    void createMonster(double health, double attackPower, double protection);
    void moveHero(CellPoint to);
    void moveEnemies();
    void moveEnemy(const CellPoint &from, const CellPoint &to);
    CellPoint generateRandomFreePoint();

    void printField(); // нужно для DEMO
    // Геттеры/Сеттеры
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

    friend class FieldScreen; // т.к FieldScreen использует проверку данных
};











