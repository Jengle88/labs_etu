#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QPainter>
#include "labs/lab5/Lab5Shaders.h"

class OpenGLWidgetLab5: public QOpenGLWidget, public QOpenGLFunctions {
public:
    explicit OpenGLWidgetLab5(QWidget *parent);

    int frameWidth = 0;
    int frameHeight = 0;

    QString imagePath = "";

    int deltaColor = 0;
    int deltaPixels = 0;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;
};
