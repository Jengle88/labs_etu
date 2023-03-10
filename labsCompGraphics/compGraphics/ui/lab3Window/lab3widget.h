#pragma once

#include <QWidget>
#include "ui_lab3widget.h"

namespace Ui {
class Lab3Widget;
}

class Lab3Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Lab3Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab3Widget();

private:
    Ui::Lab3Widget *ui;

    void init(int windowWidth, int windowHeight);

};
