//
// Created by evgeny on 21.02.23.
//

#include <QOpenGLBuffer>
#include "Lab2Primitives.h"

const std::vector<QString> Lab2Primitives::nameOfAlphaFunc = {"GL_NEVER", "GL_LESS", "GL_EQUAL", "GL_LEQUAL",
                                                              "GL_GREATER", "GL_NOTEQUAL", "GL_GEQUAL", "GL_ALWAYS"};

const std::vector<QString> Lab2Primitives::nameOfBlendFuncSFactor = {"GL_ZERO", "GL_ONE", "GL_SRC_COLOR",
                                                                     "GL_ONE_MINUS_SRC_COLOR", "GL_SRC_ALPHA",
                                                                     "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA",
                                                                     "GL_ONE_MINUS_DST_ALPHA"};

const std::vector<QString> Lab2Primitives::nameOfBlendFuncDFactor = {"GL_ZERO", "GL_ONE", "GL_DST_COLOR",
                                                                     "GL_ONE_MINUS_DST_COLOR", "GL_SRC_ALPHA",
                                                                     "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA",
                                                                     "GL_ONE_MINUS_DST_ALPHA", "GL_SRC_ALPHA_SATURATE"};

const std::vector<QString> &Lab2Primitives::getNamesOfAlphaFunc() {
    return nameOfAlphaFunc;
}

const std::vector<QString> &Lab2Primitives::getNamesOfBlendFuncSFactor() {
    return nameOfBlendFuncSFactor;
}

const std::vector<QString> &Lab2Primitives::getNamesOfBlendFuncDFactor() {
    return nameOfBlendFuncDFactor;
}

int Lab2Primitives::getAlphaFuncByName(const QString &name) {
    if (name == "GL_NEVER") return GL_NEVER;
    if (name == "GL_LESS") return GL_LESS;
    if (name == "GL_EQUAL") return GL_EQUAL;
    if (name == "GL_LEQUAL") return GL_LEQUAL;
    if (name == "GL_GREATER") return GL_GREATER;
    if (name == "GL_NOTEQUAL") return GL_NOTEQUAL;
    if (name == "GL_GEQUAL") return GL_GEQUAL;
    if (name == "GL_ALWAYS") return GL_ALWAYS;
    throw std::invalid_argument("Invalid name in getAlphaFuncByName");
}

int Lab2Primitives::getBlendFuncSFactorByName(const QString &name) {
    if (name == "GL_ZERO") return GL_ZERO;
    if (name == "GL_ONE") return GL_ONE;
    if (name == "GL_SRC_COLOR") return GL_SRC_COLOR;
    if (name == "GL_ONE_MINUS_SRC_COLOR") return GL_ONE_MINUS_SRC_COLOR;
    if (name == "GL_SRC_ALPHA") return GL_SRC_ALPHA;
    if (name == "GL_ONE_MINUS_SRC_ALPHA") return GL_ONE_MINUS_SRC_ALPHA;
    if (name == "GL_DST_ALPHA") return GL_DST_ALPHA;
    if (name == "GL_ONE_MINUS_DST_ALPHA") return GL_ONE_MINUS_DST_ALPHA;
    throw std::invalid_argument("Invalid name in getBlendFuncSFactorByName");
}

int Lab2Primitives::getBlendFuncDFactorByName(const QString &name) {
    if (name == "GL_ZERO") return GL_ZERO;
    if (name == "GL_ONE") return GL_ONE;
    if (name == "GL_DST_COLOR") return GL_DST_COLOR;
    if (name == "GL_ONE_MINUS_DST_COLOR") return GL_ONE_MINUS_DST_COLOR;
    if (name == "GL_SRC_ALPHA") return GL_SRC_ALPHA;
    if (name == "GL_ONE_MINUS_SRC_ALPHA") return GL_ONE_MINUS_SRC_ALPHA;
    if (name == "GL_DST_ALPHA") return GL_DST_ALPHA;
    if (name == "GL_ONE_MINUS_DST_ALPHA") return GL_ONE_MINUS_DST_ALPHA;
    if (name == "GL_SRC_ALPHA_SATURATE") return GL_SRC_ALPHA_SATURATE;
    throw std::invalid_argument("Invalid name in getBlendFuncDFactorByName");
}

void Lab2Primitives::makeScissors(int frameWidth, int frameHeight, double x, double y, double width, double height) {
    glEnable(GL_SCISSOR_TEST);
    glScissor(
            x * frameWidth,
            y * frameHeight,
            width * (1. - x) * frameWidth,
            height * (1. - y) * frameHeight);
    glDisable(GL_SCISSOR_TEST);
}

void Lab2Primitives::makeAlphaFunc(const QString &alphaFunc, double alphaFuncValue) {
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(Lab2Primitives::getAlphaFuncByName(alphaFunc), alphaFuncValue);
    glDisable(GL_ALPHA_TEST);
}

void Lab2Primitives::makeBlendFunc(const QString &SFactor, const QString &DFactor) {
    glEnable(GL_BLEND);
    glBlendFunc(Lab2Primitives::getBlendFuncSFactorByName(SFactor),
                Lab2Primitives::getBlendFuncDFactorByName(DFactor));
    glDisable(GL_BLEND);
}

