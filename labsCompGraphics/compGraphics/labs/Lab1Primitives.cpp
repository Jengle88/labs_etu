//
// Created by evgeny on 17.02.23.
//

#include "Lab1Primitives.h"

Lab1Primitives::Lab1Primitives() = default;

const std::vector<QString> Lab1Primitives::nameOfPrimitives = {"GL_LINES", "GL_POINTS", "GL_TRIANGLES", "GL_POLYGON",
                                                               "CLEAN"};

const std::vector<QString> &Lab1Primitives::getNameOfPrimitives() {
    return nameOfPrimitives;
}


void Lab1Primitives::drawPoints() {
    glPointSize(7.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2d(-0.5, -0.5);

        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(0.5, -0.5);

        glColor3f(0.0, 0.0, 1.0);
        glVertex2d(0.0, 0.5);
    glEnd();
}

void Lab1Primitives::drawLines() {
    glLineWidth(7.0f);
    glColor3f(0.0f, 0.3f, 0.7f);
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2d(-0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(0.5, -0.5);

        glColor3f(1.0, 0.0, 0.0);
        glVertex2d(0, 0.5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d( 0.5, 0.5);
    glEnd();
}

void Lab1Primitives::drawTriangles() {
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2d(-0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(0.5, -0.5);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2d(0.0, 0.5);
    glEnd();
}

void Lab1Primitives::drawPolygon() {
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2d(-0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(0.5, -0.5);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2d(0.0, 0.5);
    glEnd();
}

void Lab1Primitives::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
