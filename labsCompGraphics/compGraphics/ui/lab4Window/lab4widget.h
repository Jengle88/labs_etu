#pragma once

#include <QWidget>
#include "ui_lab4widget.h"

namespace Ui {
class Lab4Widget;
}

class Lab4Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Lab4Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab4Widget();

private slots:
    void on_smoothBorderSlider_valueChanged(int value);

private:
    Ui::Lab4Widget *ui;
    void init(int windowWidth, int windowHeight);
};

