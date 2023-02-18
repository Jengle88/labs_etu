//
// Created by evgeny on 17.02.23.
//
#pragma once

#include <vector>
#include <QString>
#include "GL/freeglut.h"

class Lab1Primitives {
    const std::vector<QString> nameOfPrimitives = { "GL_POINT", "GL_LINES", "GL_TRIANGLES", "GL_POLYGON" };
public:
    explicit Lab1Primitives();

    const std::vector<QString> &getNameOfPrimitives() const;

    void drawPoints() {

    }
};
