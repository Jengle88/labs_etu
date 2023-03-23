#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "labs/lab3/Lab3Fractals.h"
#include "labs/lab3/Vector.h"

class OpenGLWidgetLab3: public QOpenGLWidget, public QOpenGLFunctions {
public:
    explicit OpenGLWidgetLab3(QWidget *parent);

    int frameWidth = 0;
    int frameHeight = 0;

    int deep = 0;
    double xCenter = 0;
    double yCenter = 0;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void drawStars(double xCenter, double yCenter);

    void drawWhiteLines(double xCenter, double yCenter);

    void drawSmallRedPolygon(double xCenter, double yCenter);

    void drawWhiteStarCenter(double xCenter, double yCenter);

    void drawFractal(double xCenter, double yCenter);
};
