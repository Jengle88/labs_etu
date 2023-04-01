//
// Created by evgeny on 31.03.23.
//

#include "OpenGLWidgetLab4.h"
#include "labs/lab4/Lab4Spline.h"
#include "labs/lab1/Lab1Primitives.h"

OpenGLWidgetLab4::OpenGLWidgetLab4(QWidget *parent) {}

void OpenGLWidgetLab4::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);
}

void OpenGLWidgetLab4::resizeGL(int w, int h) {
    frameHeight = h;
    frameWidth = w;

    glViewport(0, 0, frameWidth, frameHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidgetLab4::paintGL() {
    glColor3f(1.0f, 1.0f, 1.0f);
    if (smoothBorder > 0)
        Lab4Spline::drawCurve(points, smoothBorder);
    else
        Lab1Primitives::clear();
}
