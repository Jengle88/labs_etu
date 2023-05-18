#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>
#include <cmath>
#include "labs/lab6/Vector2D.h"
#include "labs/lab6/Vector3D.h"

class OpenGLWidgetLab6 : public QOpenGLWidget, public QOpenGLFunctions {
public:
    explicit OpenGLWidgetLab6(QWidget *parent);

    int frameWidth = 0;
    int frameHeight = 0;
    enum CameraState {
        CAMERA_IDLE, CAMERA_ROTATING, CAMERA_MOVING
    };

    CameraState cameraState = CAMERA_IDLE;
    Vector3D cameraPosition = {0, -2, -6};
    Vector2D prevPoint = {0, 0};
    Vector2D cameraRotation = {1, 0};
    double cameraZoom = 0.85;

    double scx = 0.1, scy = 0.1, scz = 0.1;
    double hpa = 0.7, hpb = 0.6, hpc = 5.4;


protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    Vector2D screenCoordsToGL(double x, double y);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void draw1Figure();

    void draw2Figure();

    void draw3Figure();

    void draw4Figure();

    void systemCoordinates();
};


