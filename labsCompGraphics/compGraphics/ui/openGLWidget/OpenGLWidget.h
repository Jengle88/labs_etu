//
// Created by evgeny on 18.02.23.
//
#pragma once


#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidget : public QOpenGLWidget {
public:
    explicit OpenGLWidget(QWidget *parent);
    void update(const QString& newFigure);

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    QString currentFigureForRepaint;
};
