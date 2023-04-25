//
// Created by evgeny on 14.04.23.
//

#include "OpenGLWidgetLab5.h"
#include "labs/lab5/Lab5Shaders.h"

OpenGLWidgetLab5::OpenGLWidgetLab5(QWidget *parent) {}

void OpenGLWidgetLab5::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);
}

void OpenGLWidgetLab5::resizeGL(int w, int h) {
    frameHeight = h;
    frameWidth = w;

    glViewport(0, 0, frameWidth, frameHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidgetLab5::paintGL() {
    if (!imagePath.isEmpty()) {
        QImage image(imagePath);
        if (deltaColor > 0 && deltaPixels > 0) {
            Lab5Shaders::makeWaveEffect(image, deltaColor, deltaPixels);
        }
        QRectF target(0, 0, frameWidth, frameHeight);
        QPainter(this).drawImage(target, image);
    }
}
