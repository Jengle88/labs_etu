//
// Created by evgeny on 17.02.23.
//
#pragma once

#include <vector>
#include <QString>
#include "GL/freeglut.h"
#include <QList>
#include "labs/lab2/Lab2Primitives.h"

class Lab1Primitives {
private:
    static const QList<QString> nameOfPrimitives;
public:
    explicit Lab1Primitives();

    static const QList<QString> &getNameOfPrimitives();

    static void drawPoints();

    static void drawLines();

    static void drawTriangles();

    static void drawQuads();

    static void drawPolygon();

    static void clear();
};
