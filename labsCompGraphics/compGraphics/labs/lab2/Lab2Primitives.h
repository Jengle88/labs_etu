//
// Created by evgeny on 21.02.23.
//
#pragma once

#include <vector>
#include <QString>

class Lab2Primitives {
private:
    static const std::vector<QString> nameOfAlphaFunc;
    static int getAlphaFuncByName(const QString& name);

    static const std::vector<QString> nameOfBlendFuncSFactor;
    static int getBlendFuncSFactorByName(const QString& name);

    static const std::vector<QString> nameOfBlendFuncDFactor;
    static int getBlendFuncDFactorByName(const QString& name);

public:
    static const std::vector<QString> &getNamesOfAlphaFunc();

    static const std::vector<QString> &getNamesOfBlendFuncSFactor();

    static const std::vector<QString> &getNamesOfBlendFuncDFactor();

    static void makeScissors(int frameWidth, int frameHeight, double x, double y, double width, double height);

    static void makeAlphaFunc(const QString& alphaFunc, double alphaFuncValue);

    static void makeBlendFunc(const QString& SFactor, const QString& DFactor);
};
