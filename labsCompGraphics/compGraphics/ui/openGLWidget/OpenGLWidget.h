//
// Created by evgeny on 18.02.23.
//
#pragma once


#include <QtWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <iostream>
#include "labs/lab1/Lab1Primitives.h"

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
public:
    explicit OpenGLWidget(QWidget *parent);

    void setFigure(const QString &newFigure);

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    QString currentFigureForRepaint;

    int frameWidth = 0;
    int frameHeight = 0;
};
