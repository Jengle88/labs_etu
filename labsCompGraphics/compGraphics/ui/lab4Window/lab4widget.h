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

    void on_p1XSlider_valueChanged(int value);

    void on_p1YSlider_valueChanged(int value);

    void on_p2XSlider_valueChanged(int value);

    void on_p2YSlider_valueChanged(int value);

    void on_p3XSlider_valueChanged(int value);

    void on_p3YSlider_valueChanged(int value);

    void on_p4XSlider_valueChanged(int value);

    void on_p4YSlider_valueChanged(int value);

    void on_p5XSlider_valueChanged(int value);

    void on_p5YSlider_valueChanged(int value);

    void on_p6XSlider_valueChanged(int value);

    void on_p6YSlider_valueChanged(int value);

private:
    Ui::Lab4Widget *ui;
    void init(int windowWidth, int windowHeight);
};

