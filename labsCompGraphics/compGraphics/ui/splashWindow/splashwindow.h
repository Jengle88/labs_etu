#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_splashwindow.h"
#include "ui/lab1Window/lab1widget.h"
#include "ui/lab2Window/lab2widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SplashWindow; }
QT_END_NAMESPACE

class SplashWindow : public QMainWindow {

    Lab1Widget *lab1Widget;
    Lab2Widget *lab2Widget;
    Q_OBJECT

public:
    SplashWindow(int windowWidth,
                 int windowHeight,
                 QWidget *parent = nullptr);

    ~SplashWindow();


private slots:
    void on_buttonLab1_clicked();

    void on_buttonLab2_clicked();

private:
    Ui::SplashWindow *ui;

    void init(int windowWidth, int windowHeight);

    void safeShowWidget(QWidget* widget);
};
