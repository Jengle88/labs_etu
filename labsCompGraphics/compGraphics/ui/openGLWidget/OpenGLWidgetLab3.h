#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidgetLab3: public QOpenGLWidget, public QOpenGLFunctions {
public:
    explicit OpenGLWidgetLab3(QWidget *parent);

    int frameWidth = 0;
    int frameHeight = 0;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

};
