#pragma once

#include <QOpenGLWidget>
#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QPainter>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

class OpenGLWidgetLab5: public QOpenGLWidget, public QOpenGLFunctions {
public:
    explicit OpenGLWidgetLab5(QWidget *parent);

    QOpenGLShaderProgram shaderProgram;

    int frameWidth = 0;
    int frameHeight = 0;

    QString imagePath = "";

    int deltaColor = 0;
    int deltaPixels = 0;

    QOpenGLTexture* texture;
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;
    QVector<QVector3D> waveEffectParams;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void initShaders();
};
