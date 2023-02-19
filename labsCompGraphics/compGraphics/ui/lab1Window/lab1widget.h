#pragma once

#include <QWidget>
#include <QComboBox>
#include <memory>
#include "ui_lab1widget.h"
#include "labs/Lab1Primitives.h"
#include "ui/openGLWidget/OpenGLWidget.h"

namespace Ui { class Lab1Widget; }

class Lab1Widget : public QWidget
{
    Q_OBJECT
    QStringList listOfNamePrimitives;
public:
    explicit Lab1Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab1Widget();

private slots:
    void on_selectPrimitive_currentIndexChanged(const QString &newPrimitive);

private:
    Ui::Lab1Widget *ui;

    void init(int windowWidth, int windowHeight);

    void setDropdownMenuOfPrimitives();

    void loadListOfNamePrimitives();

};
