//
// Created by evgeny on 21.02.23.
//
#pragma once

#include <vector>
#include <QString>
#include <QOpenGLBuffer>
#include <iostream>
#include <QMap>
#include "GL/freeglut.h"

class Lab2Primitives {
private:
    static const QMap<QString, int> mapOfAlphaFunc;
    static const QList<QString> namesOfAlphaFunc;
    static int getAlphaFuncByName(const QString& name);

    static const QMap<QString, int> mapOfBlendFuncSFactor;
    static const QList<QString> nameOfBlendFuncSFactor;
    static int getBlendFuncSFactorByName(const QString& name);

    static const QMap<QString, int> mapOfBlendFuncDFactor;
    static const QList<QString> nameOfBlendFuncDFactor;
    static int getBlendFuncDFactorByName(const QString& name);

public:
    static QList<QString> getNamesOfAlphaFunc();

    static QList<QString> getNamesOfBlendFuncSFactor();

    static QList<QString> getNamesOfBlendFuncDFactor();

    static void makeScissors(int frameWidth, int frameHeight, double x, double y, double width, double height);

    static void makeAlphaFunc(const QString& alphaFunc, double alphaFuncValue);

    static void makeBlendFunc(const QString& SFactor, const QString& DFactor);

    static void disableScissors();

    static void disableAlphaFunc();

    static void disableBlendFunc();
};
