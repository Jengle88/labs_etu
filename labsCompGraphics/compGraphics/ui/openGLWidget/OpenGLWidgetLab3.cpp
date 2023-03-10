//
// Created by evgeny on 09.03.23.
//

#include "OpenGLWidgetLab3.h"
#include "labs/lab3/Lab3Fractals.h"

OpenGLWidgetLab3::OpenGLWidgetLab3(QWidget *parent): QOpenGLWidget(parent) {}

void OpenGLWidgetLab3::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);
}

void OpenGLWidgetLab3::resizeGL(int w, int h) {
    frameHeight = h;
    frameWidth = w;

    glViewport(0, 0, frameWidth, frameHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidgetLab3::paintGL() {
    glColor3f(1.0f, 0.2f, 0.5f);
    glBegin(GL_LINES);
    Lab3Fractals::drawFractal(0, 0, 0.5, 0, 7);
    glEnd();
    glFlush();
}
