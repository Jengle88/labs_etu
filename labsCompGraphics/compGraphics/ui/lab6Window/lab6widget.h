#ifndef LAB6WIDGET_H
#define LAB6WIDGET_H

#include <QWidget>

namespace Ui {
class Lab6Widget;
}

class Lab6Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Lab6Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab6Widget();

private slots:

    void on_resetCamera_clicked();

    void on_globalScaleSlider_valueChanged(int value);

private:
    Ui::Lab6Widget *ui;
    void init(int windowWidth, int windowHeight);
};

#endif // LAB6WIDGET_H
