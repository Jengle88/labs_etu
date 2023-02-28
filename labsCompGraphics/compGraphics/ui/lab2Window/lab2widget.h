#pragma once

#include <QWidget>
#include "ui/lab1Window/lab1widget.h"
#include "ui_lab2widget.h"
#include "labs/lab2/Lab2Primitives.h"

namespace Ui {
class Lab2Widget;
}

class Lab2Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Lab2Widget(int windowWidth, int windowHeight, QWidget *parent = nullptr);
    ~Lab2Widget();

private slots:
    void on_selectPrimitive_currentIndexChanged(const QString &arg1);

    void on_scissorEnable_clicked();

    void on_alphaFuncEnable_clicked();

    void on_blendFuncEnable_clicked();

    void on_xSlider_valueChanged(int value);

    void on_ySlider_valueChanged(int value);

    void on_widthSlider_valueChanged(int value);

    void on_heightSlider_valueChanged(int value);

    void on_alphaFuncSelect_currentIndexChanged(const QString &arg1);

    void on_alphaFuncSlider_valueChanged(int value);

    void on_blendSFactorSelect_currentIndexChanged(const QString &arg1);

    void on_blendDFactorSelect_currentIndexChanged(const QString &arg1);

private:
    Ui::Lab2Widget *ui;

    void init(int windowWidth, int windowHeight);

    void setQComboBoxMenu(const QStringList &listOfItems, QComboBox *qComboBox);

    QStringList vectorOfQStringToQStringList(const QList<QString>& src);

    void updateOpenGLWidgetState();
};
