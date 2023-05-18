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
    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_doubleSpinBox_5_valueChanged(double arg1);

    void on_doubleSpinBox_6_valueChanged(double arg1);

private:
    Ui::Lab6Widget *ui;
    void init(int windowWidth, int windowHeight);
};

#endif // LAB6WIDGET_H
