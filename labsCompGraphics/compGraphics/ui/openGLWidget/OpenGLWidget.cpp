//
// Created by evgeny on 18.02.23.
//


#include <iostream>
#include "OpenGLWidget.h"
#include "labs/Lab1Primitives.h"

OpenGLWidget::OpenGLWidget(QWidget *parent): QOpenGLWidget(parent) { }

void OpenGLWidget::initializeGL() {
    glClearColor(0,0,0,1);
    glViewport(0, 0, 10, 10);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);

}

void OpenGLWidget::resizeGL(int w, int h) {
    QOpenGLWidget::resizeGL(w, h);
}

void OpenGLWidget::paintGL() {
    std::cout << currentFigureForRepaint.toStdString() << "\n";
    Lab1Primitives::clear();
    if (currentFigureForRepaint == "GL_POINTS")
        Lab1Primitives::drawPoints();
    else if (currentFigureForRepaint == "GL_LINES")
        Lab1Primitives::drawLines();
    else if (currentFigureForRepaint == "GL_TRIANGLES")
        Lab1Primitives::drawTriangles();
    else if (currentFigureForRepaint == "GL_POLYGON")
        Lab1Primitives::drawPolygon();

}

void OpenGLWidget::update(const QString &newFigure) {
    currentFigureForRepaint = newFigure;
    repaint();
}
