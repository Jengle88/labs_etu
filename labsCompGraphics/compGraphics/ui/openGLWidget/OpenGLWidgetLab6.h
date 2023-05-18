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

    double globalScale = 3;


protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    Vector2D screenCoordsToGL(double x, double y);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void draw1Figure(double scale);

    void draw2Figure(double scale);

    void draw3Figure(double scale);

    void draw4Figure(double scale);

    void systemCoordinates();
};


