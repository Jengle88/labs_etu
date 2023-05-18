//
// Created by evgeny on 01.05.23.
//

#include <cmath>
#include "OpenGLWidgetLab6.h"
#include "labs/lab6/Painter.h"

OpenGLWidgetLab6::OpenGLWidgetLab6(QWidget *parent) {}

void OpenGLWidgetLab6::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);

}

void OpenGLWidgetLab6::resizeGL(int w, int h) {
    frameHeight = h;
    frameWidth = w;

    glViewport(0, 0, frameWidth, frameHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidgetLab6::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glFrustum(-1, 1, -1, 1, 2, 30);

    glMatrixMode(GL_MODELVIEW);

    // camera
    glTranslated(cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glScaled(cameraZoom, cameraZoom, cameraZoom);
    glRotated(-cameraRotation.y * M_PI * 12 * 1, 1, 0, 0);
    glRotated(cameraRotation.x * M_PI * 12 * 1, 0, 1, 0);

    glColor3d(1, 1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    draw1Figure(globalScale);
    draw2Figure(globalScale);
    draw3Figure(globalScale);
    draw4Figure(globalScale);

    systemCoordinates();
}

void OpenGLWidgetLab6::draw1Figure(double scale) {
    glPushMatrix();
    glTranslated(2 * scale, 0, -1);
    glScaled(0.1 * scale, 1.3 * scale, 1.5 * scale);
    glRotated(90, 0, 1, 0);
    Painter::wheel(0.6, 0.6, 6.7);
    glPopMatrix();
}

void OpenGLWidgetLab6::draw2Figure(double scale) {
    glPushMatrix();
    glTranslated(5 * scale, 0, -1);
    glScaled(0.04 * scale, 1.5 * scale, 1 * scale);
    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 0, 1);
    Painter::button(0.7, 0.7, 6.7, 1, 1, 30.5);
    glPopMatrix();
}

void OpenGLWidgetLab6::draw3Figure(double scale) {
    glPushMatrix();
    glTranslated(8 * scale, 0, -1);
    glScaled(0.1 * scale, 1.3 * scale, 1.5 * scale);
    glRotated(90, 0, 1, 0);
    Painter::doorhandle(0.6, 0.6, 6.7, 0.7, 0.7, 4.5);
    glPopMatrix();
}

void OpenGLWidgetLab6::draw4Figure(double scale) {
    glPushMatrix();
    glTranslated(11 * scale, 0, -1);
    glScaled(0.2 * scale, 0.3 * scale, 0.3 * scale);
    glRotated(90, 0, 1, 1);
    Painter::sandClock(0.3, 0.3, 1.1);
    glPopMatrix();
}

void OpenGLWidgetLab6::systemCoordinates() {
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(1, 1, 1);
    Painter::systemCoordinates();
    glPopMatrix();
}

Vector2D OpenGLWidgetLab6::screenCoordsToGL(double x, double y) {
    return {(x / frameWidth * 2 - 1), (-(y / frameHeight * 2 - 1))};
}

void OpenGLWidgetLab6::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && cameraState == CAMERA_ROTATING ||
        event->button() == Qt::MiddleButton && cameraState == CAMERA_MOVING)
        cameraState = CAMERA_IDLE;
}

void OpenGLWidgetLab6::mouseMoveEvent(QMouseEvent *event) {
    if (cameraState == CAMERA_ROTATING) {
        Vector2D pointer = screenCoordsToGL(event->pos().x(), event->pos().y());
        cameraRotation.x += pointer.x - prevPoint.x;
        cameraRotation.y += pointer.y - prevPoint.y;
        prevPoint = screenCoordsToGL(event->pos().x(), event->pos().y());
    } else if (cameraState == CAMERA_MOVING) {
        Vector2D pointer = screenCoordsToGL(event->pos().x(), event->pos().y());
        cameraPosition.x += pointer.x - prevPoint.x;
        cameraPosition.y += pointer.y - prevPoint.y;
        prevPoint = screenCoordsToGL(event->pos().x(), event->pos().y());
    }
    update();
}

void OpenGLWidgetLab6::mousePressEvent(QMouseEvent *event) {
    prevPoint = screenCoordsToGL(event->pos().x(), event->pos().y());
    if (cameraState == CAMERA_IDLE) {
        if (event->button() == Qt::LeftButton)
            cameraState = CAMERA_ROTATING;
        else if (event->button() == Qt::MiddleButton)
            cameraState = CAMERA_MOVING;
    }
}

void OpenGLWidgetLab6::wheelEvent(QWheelEvent *event) {
    cameraZoom += event->angleDelta().y() / 120. / 30.;
    if (cameraZoom <= 0.2) cameraZoom = 0.2;
    if (cameraZoom >= 10) cameraZoom = 10;
    update();
}
