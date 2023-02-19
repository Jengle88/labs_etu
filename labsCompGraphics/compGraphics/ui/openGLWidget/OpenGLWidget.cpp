//
// Created by evgeny on 18.02.23.
//

#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent): QOpenGLWidget(parent) { }

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);
}

void OpenGLWidget::resizeGL(int w, int h) {
    frameHeight = h;
    frameWidth = w;

    glViewport(0, 0, frameWidth, frameHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidget::paintGL() {
//    std::cout << currentFigureForRepaint.toStdString() << "\n";
    Lab1Primitives::clear();
    if (currentFigureForRepaint == "GL_POINTS")
        Lab1Primitives::drawPoints();
    else if (currentFigureForRepaint == "GL_LINES")
        Lab1Primitives::drawLines();
    else if (currentFigureForRepaint == "GL_TRIANGLES")
        Lab1Primitives::drawTriangles();
    else if (currentFigureForRepaint == "GL_QUADS")
        Lab1Primitives::drawQuads();
    else if (currentFigureForRepaint == "GL_POLYGON")
        Lab1Primitives::drawPolygon();
}

void OpenGLWidget::setFigure(const QString &newFigure) {
    currentFigureForRepaint = newFigure;
    update();
}
