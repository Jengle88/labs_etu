#pragma once

#include <QWidget>
#include <QComboBox>
#include <memory>
#include "ui_lab1widget.h"

namespace Ui { class Lab1Widget; }

class Lab1Widget : public QWidget
{
    QComboBox* selectPrimitive;
    Q_OBJECT


public:
    explicit Lab1Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab1Widget();

private:
    Ui::Lab1Widget *ui;

    void init(int windowWidth, int windowHeight);

    void on_selectPrimitive_activated(const QString &arg1);
};
