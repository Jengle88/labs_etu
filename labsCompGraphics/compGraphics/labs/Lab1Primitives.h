//
// Created by evgeny on 17.02.23.
//
#pragma once

#include <vector>
#include <QString>
#include "GL/freeglut.h"

class Lab1Primitives {
private:
    static const std::vector<QString> nameOfPrimitives;
public:
    explicit Lab1Primitives();

    static const std::vector<QString> &getNameOfPrimitives();

    static void drawPoints();

    static void drawLines();

    static void drawTriangles();

    static void clear();

    static void drawPolygon();
};
