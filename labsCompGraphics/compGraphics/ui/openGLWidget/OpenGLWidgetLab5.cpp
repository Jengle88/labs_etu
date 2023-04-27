//
// Created by evgeny on 14.04.23.
//

#include "OpenGLWidgetLab5.h"

OpenGLWidgetLab5::OpenGLWidgetLab5(QWidget *parent) {}

void OpenGLWidgetLab5::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_BUFFER_BIT);

    initShaders();
}

void OpenGLWidgetLab5::initShaders() {
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "/home/evgeny/git/labs_etu/labsCompGraphics/compGraphics/labs/lab5/vert.vsh");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "/home/evgeny/git/labs_etu/labsCompGraphics/compGraphics/labs/lab5/frag.vsh");

    texCoords.append(QVector2D(0, 0));
    texCoords.append(QVector2D(1, 0));
    texCoords.append(QVector2D(1, 1));
    texCoords.append(QVector2D(0, 1));

    vertices.append(QVector3D(1, 1, 0));
    vertices.append(QVector3D(-1, 1, 0));
    vertices.append(QVector3D(-1, -1, 0));
    vertices.append(QVector3D(1, -1, 0));

    shaderProgram.bindAttributeLocation("vertex", 0);
    shaderProgram.bindAttributeLocation("texCoord", 1);

    shaderProgram.link();
    shaderProgram.bind();
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

        QImage timg = image;
        texture = new QOpenGLTexture(timg);
        texture->bind();

        shaderProgram.enableAttributeArray(0);
        shaderProgram.enableAttributeArray(1);
        shaderProgram.enableAttributeArray(2);
        shaderProgram.setAttributeArray(0, vertices.constData());
        shaderProgram.setAttributeArray(1, texCoords.constData());
        shaderProgram.setUniformValue("texture", 0);
        glDrawArrays(GL_POLYGON, 0, 4);

        delete texture;

    }
}
