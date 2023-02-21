#ifndef LAB2WIDGET_H
#define LAB2WIDGET_H

#include <QWidget>
#include "ui/lab1Window/lab1widget.h"

namespace Ui {
class Lab2Widget;
}

class Lab2Widget : public QWidget
{
    Q_OBJECT
    QStringList listOfNamePrimitives;

public:
    explicit Lab2Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab2Widget();

private slots:
    void on_selectPrimitive_currentIndexChanged(const QString &arg1);

private:
    Ui::Lab2Widget *ui;

    void init(int windowWidth, int windowHeight);

    void setDropdownMenuOfPrimitives();

    void loadListOfNamePrimitives();
};

#endif // LAB2WIDGET_H
