//
// Created by evgeny on 21.02.23.
//

#include "Lab2Primitives.h"

const QMap<QString, int> Lab2Primitives::mapOfAlphaFunc = QMap<QString, int>({{"GL_NEVER",    GL_NEVER},
                                                                              {"GL_LESS",     GL_LESS},
                                                                              {"GL_EQUAL",    GL_EQUAL},
                                                                              {"GL_LEQUAL",   GL_LEQUAL},
                                                                              {"GL_GREATER",  GL_GREATER},
                                                                              {"GL_NOTEQUAL", GL_NOTEQUAL},
                                                                              {"GL_GEQUAL",   GL_GEQUAL},
                                                                              {"GL_ALWAYS",   GL_ALWAYS}});
const QList<QString> Lab2Primitives::namesOfAlphaFunc = mapOfAlphaFunc.keys();

const QMap<QString, int> Lab2Primitives::mapOfBlendFuncSFactor = {{"GL_ZERO",                GL_ZERO},
                                                                  {"GL_ONE",                 GL_ONE},
                                                                  {"GL_DST_COLOR",           GL_DST_COLOR},
                                                                  {"GL_ONE_MINUS_DST_COLOR", GL_ONE_MINUS_DST_COLOR},
                                                                  {"GL_SRC_ALPHA",           GL_SRC_ALPHA},
                                                                  {"GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA},
                                                                  {"GL_DST_ALPHA",           GL_DST_ALPHA},
                                                                  {"GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA},
                                                                  {"GL_SRC_ALPHA_SATURATE",  GL_SRC_ALPHA_SATURATE}};
const QList<QString> Lab2Primitives::nameOfBlendFuncSFactor = mapOfBlendFuncSFactor.keys();

const QMap<QString, int> Lab2Primitives::mapOfBlendFuncDFactor = {{"GL_ZERO",                GL_ZERO},
                                                                  {"GL_ONE",                 GL_ONE},
                                                                  {"GL_SRC_COLOR",           GL_SRC_COLOR},
                                                                  {"GL_ONE_MINUS_SRC_COLOR", GL_ONE_MINUS_SRC_COLOR},
                                                                  {"GL_SRC_ALPHA",           GL_SRC_ALPHA},
                                                                  {"GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA},
                                                                  {"GL_DST_ALPHA",           GL_DST_ALPHA},
                                                                  {"GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA}};
const QList<QString> Lab2Primitives::nameOfBlendFuncDFactor = mapOfBlendFuncDFactor.keys();

QList<QString> Lab2Primitives::getNamesOfAlphaFunc() {
    return namesOfAlphaFunc;
}

QList<QString> Lab2Primitives::getNamesOfBlendFuncSFactor() {
    return nameOfBlendFuncSFactor;
}

QList<QString> Lab2Primitives::getNamesOfBlendFuncDFactor() {
    return nameOfBlendFuncDFactor;
}

int Lab2Primitives::getAlphaFuncByName(const QString &name) {
    if (mapOfAlphaFunc.contains(name))
        return mapOfAlphaFunc[name];

    throw std::invalid_argument("Invalid name in getAlphaFuncByName");
}

int Lab2Primitives::getBlendFuncSFactorByName(const QString &name) {
    if (mapOfBlendFuncSFactor.contains(name))
        return mapOfBlendFuncSFactor[name];

    throw std::invalid_argument("Invalid name in getBlendFuncSFactorByName");
}

int Lab2Primitives::getBlendFuncDFactorByName(const QString &name) {
    if (mapOfBlendFuncDFactor.contains(name))
        return mapOfBlendFuncDFactor[name];

    throw std::invalid_argument("Invalid name in getBlendFuncDFactorByName");
}

void Lab2Primitives::makeScissors(int frameWidth, int frameHeight, double x, double y, double width, double height) {
    glEnable(GL_SCISSOR_TEST);
    glScissor(
            x * frameWidth,
            y * frameHeight,
            width * (1. - x) * frameWidth,
            height * (1. - y) * frameHeight);
}

void Lab2Primitives::disableScissors() { glDisable(GL_SCISSOR_TEST); }

void Lab2Primitives::makeAlphaFunc(const QString &alphaFunc, double alphaFuncValue) {
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(Lab2Primitives::getAlphaFuncByName(alphaFunc), alphaFuncValue);
}

void Lab2Primitives::disableAlphaFunc() { glDisable(GL_ALPHA_TEST); }

void Lab2Primitives::makeBlendFunc(const QString &SFactor, const QString &DFactor) {
    glEnable(GL_BLEND);
    glBlendFunc(Lab2Primitives::getBlendFuncSFactorByName(SFactor),
                Lab2Primitives::getBlendFuncDFactorByName(DFactor));
}

void Lab2Primitives::disableBlendFunc() { glDisable(GL_BLEND); }

