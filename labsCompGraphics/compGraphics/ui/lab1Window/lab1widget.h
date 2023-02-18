#pragma once

#include <QWidget>
#include <QComboBox>
#include <memory>
#include "ui_lab1widget.h"
#include "labs/Lab1Primitives.h"

namespace Ui { class Lab1Widget; }

class Lab1Widget : public QWidget
{
    Q_OBJECT
    Lab1Primitives lab1Primitives = Lab1Primitives();
public:
    explicit Lab1Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab1Widget();

private:
    Ui::Lab1Widget *ui;

    void init(int windowWidth, int windowHeight);

    void loadListOfNamePrimitives();

    void on_selectPrimitive_currentIndexChanged(const QString &newPrimitive);
};
