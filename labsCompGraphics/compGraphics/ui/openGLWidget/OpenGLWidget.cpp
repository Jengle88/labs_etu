//
// Created by evgeny on 18.02.23.
//

#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
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
    Lab1Primitives::clear();
    runAreaParams();
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
    stopAreaParams();
}

void OpenGLWidget::setFigure(const QString &newFigure) {
    currentFigureForRepaint = newFigure;
    update();
}

void OpenGLWidget::runAreaParams() const {
    if (scissorEnable) {
        Lab2Primitives::makeScissors(
                frameWidth, frameHeight, scissorX, scissorY, scissorWidth, scissorHeight);
    }
    if (alphaEnable) {
        Lab2Primitives::makeAlphaFunc(alphaFunc, alphaFuncValue);
    }

    if (blendFactorEnable) {
        Lab2Primitives::makeBlendFunc(sFactor, dFactor);
    }
}

void OpenGLWidget::stopAreaParams() const {
    if (scissorEnable) Lab2Primitives::disableScissors();
    if (alphaEnable) Lab2Primitives::disableAlphaFunc();
    if (blendFactorEnable) Lab2Primitives::disableBlendFunc();
}

void OpenGLWidget::setScissorParams(bool scissorEnable, double x, double y, double width, double height) {
    this->scissorEnable = scissorEnable;
    this->scissorX = x;
    this->scissorY = y;
    this->scissorWidth = width;
    this->scissorHeight = height;
}

void OpenGLWidget::setAlphaParams(bool alphaEnable, const QString &alphaFunc, double alphaFuncValue) {
    this->alphaEnable = alphaEnable;
    this->alphaFunc = alphaFunc;
    this->alphaFuncValue = alphaFuncValue;
}

void OpenGLWidget::setBlendFactorParams(bool blendFactorEnable, const QString &sFactor, const QString &dFactor) {
    this->blendFactorEnable = blendFactorEnable;
    this->sFactor = sFactor;
    this->dFactor = dFactor;
}

void OpenGLWidget::runAreaParams() {
    if (scissorEnable) {
        Lab2Primitives::makeScissors(
                frameWidth, frameHeight, scissorX, scissorY, scissorWidth, scissorHeight);
    }
    if (alphaEnable) {
        Lab2Primitives::makeAlphaFunc(alphaFunc, alphaFuncValue);
    }

    if (blendFactorEnable) {
        Lab2Primitives::makeBlendFunc(sFactor, dFactor);
    }
}

void OpenGLWidget::stopAreaParams() const {
    if (scissorEnable) Lab2Primitives::disableScissors();
    if (alphaEnable) Lab2Primitives::disableAlphaFunc();
    if (blendFactorEnable) Lab2Primitives::disableBlendFunc();
}

void OpenGLWidget::setScissorParams(bool scissorEnable, double x, double y, double width, double height) {
    this->scissorEnable = scissorEnable;
    this->scissorX = x;
    this->scissorY = y;
    this->scissorWidth = width;
    this->scissorHeight = height;
}

void OpenGLWidget::setAlphaParams(bool alphaEnable, const QString &alphaFunc, double alphaFuncValue) {
    this->alphaEnable = alphaEnable;
    this->alphaFunc = alphaFunc;
    this->alphaFuncValue = alphaFuncValue;
}

void OpenGLWidget::setBlendFactorParams(bool blendFactorEnable, const QString &sFactor, const QString &dFactor) {
    this->blendFactorEnable = blendFactorEnable;
    this->sFactor = sFactor;
    this->dFactor = dFactor;
}
