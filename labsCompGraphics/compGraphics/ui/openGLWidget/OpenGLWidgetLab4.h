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
    std::vector<Point> points = {
            Point(0, 0), Point(-0.4, 0.3),
            Point(-0.2, 0.9), Point(0.3, 1.2),
            Point(0.8, 0.8), Point(0.7, 0.1)};

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;
};
