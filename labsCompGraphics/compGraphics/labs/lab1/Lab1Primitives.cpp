//
// Created by evgeny on 17.02.23.
//

#include "Lab1Primitives.h"

Lab1Primitives::Lab1Primitives() = default;

const QList<QString> Lab1Primitives::nameOfPrimitives = {"GL_POINTS", "GL_LINES", "GL_TRIANGLES", "GL_QUADS",
                                                         "GL_POLYGON", "CLEAN"};

const QList<QString> &Lab1Primitives::getNameOfPrimitives() {
    return nameOfPrimitives;
}

void Lab1Primitives::drawPoints() {
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex2d(-0.5, -0.5);

        glColor4f(0.0, 1.0, 0.0, 0.7);
        glVertex2d(0.5, -0.5);

        glColor4f(0.0, 0.0, 1.0, 0.5);
        glVertex2d(0.0, 0.5);
    glEnd();
}

void Lab1Primitives::drawLines() {
    glLineWidth(3.0f);
    glColor4f(0.0f, 0.3f, 0.7f, 1.0f);
    glBegin(GL_LINES);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex2d(-0.5, -0.5);
        glColor4f(0.0, 1.0, 0.0, 0.7);
        glVertex2d(0.5, -0.5);

        glColor4f(1.0, 0.0, 0.0, 0.8);
        glVertex2d(-0.25, 0);
        glColor4f(0.0, 1.0, 0.0, 0.5);
        glVertex2d(0.5, 0);

        glColor4f(1.0, 0.0, 0.0, 0.6);
        glVertex2d(0, 0.5);
        glColor4f(0.0, 1.0, 0.0, 0.3);
        glVertex2d(0.5, 0.5);
    glEnd();
}

void Lab1Primitives::drawTriangles() {
    glBegin(GL_TRIANGLES);
        glColor4f(1.0, 0.0, 0.0, 0.8);
        glVertex2d(-0.5, -0.5);
        glColor4f(0.0, 1.0, 0.0, 0.5);
        glVertex2d(0.5, -0.5);
        glColor4f(0.0, 0.0, 1.0, 0.6);
        glVertex2d(0.0, 0.5);
    glEnd();
}

void Lab1Primitives::drawQuads() {
    glBegin(GL_QUADS);
        glColor4f(1.0, 0.0, 0.0, 0.3);
        glVertex2d(-0.5, -0.5);
        glColor4f(0.0, 1.0, 0.0, 0.7);
        glVertex2d(0.5, -0.5);
        glColor4f(0.0, 0.0, 1.0, 0.1);
        glVertex2d(0.5, 0.5);
        glColor4f(0.0, 0.0, 1.0, 0.2);
        glVertex2d(-0.5, 0.5);
    glEnd();
}

void Lab1Primitives::drawPolygon() {
    glBegin(GL_POLYGON);
        glColor4f(1.0, 0.0, 0.0, 0.9);
        glVertex2d(-0.5, -0.5);
        glColor4f(0.0, 1.0, 0.0, 0.4);
        glVertex2d(0.5, -0.5);
        glColor4f(0.0, 0.0, 1.0, 0.7);
        glVertex2d(-0.5, 0.5);
        glColor4f(0.0, 1.0, 1.0, 0.3);
        glVertex2d(0.5, 0.5);
    glEnd();
}

void Lab1Primitives::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
