#pragma once

#include <QWidget>

namespace Ui {
class Lab5Widget;
}

class Lab5Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Lab5Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab5Widget();

private slots:
    void on_chooseFile_clicked();

    void on_deltaPixelsSlider_valueChanged(int value);

    void on_deltaColorSlider_valueChanged(int value);

private:
    Ui::Lab5Widget *ui;
    void init(int windowWidth, int windowHeight);
};
