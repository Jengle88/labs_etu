//
// Created by evgeny on 18.02.23.
//
#pragma once

#include <QtWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <iostream>
#include "labs/lab1/Lab1Primitives.h"
#include "labs/lab2/Lab2Primitives.h"

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
public:
    explicit OpenGLWidget(QWidget *parent);

    int frameWidth = 0;
    int frameHeight = 0;

    void setFigure(const QString &newFigure);

    void setScissorParams(bool scissorEnable, double x, double y, double width, double height);

    void setAlphaParams(bool alphaEnable, const QString &alphaFunc, double alphaFuncValue);

    void setBlendFactorParams(bool blendFactorEnable, const QString &sFactor, const QString &dFactor);
protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;
private:
    QString currentFigureForRepaint;

    bool scissorEnable = false;
    double scissorX = 0;
    double scissorY = 0;
    double scissorWidth = 0;
    double scissorHeight = 0;

    bool alphaEnable = false;
    QString alphaFunc;
    double alphaFuncValue = 0;

    bool blendFactorEnable = false;
    QString sFactor;
    QString dFactor;

    void runAreaParams() const;
    void stopAreaParams() const;
};
