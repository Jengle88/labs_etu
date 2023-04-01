#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "labs/lab3/Lab3Fractals.h"
#include "labs/lab3/Vector.h"

class OpenGLWidgetLab4: public QOpenGLWidget, public QOpenGLFunctions {
public:
    explicit OpenGLWidgetLab4(QWidget *parent);

    int frameWidth = 0;
    int frameHeight = 0;

    double smoothBorder = 2;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;
};
