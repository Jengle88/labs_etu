#pragma once

#include <QMainWindow>
#include "ui_splashwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SplashWindow; }
QT_END_NAMESPACE

class SplashWindow : public QMainWindow {
Q_OBJECT

public:
    SplashWindow(int windowWidth,
                 int windowHeight,
                 QWidget *parent = nullptr)
            : QMainWindow(parent), ui(new Ui::SplashWindow) {
        ui->setupUi(this);
        setMinimumWidth(windowWidth);
        setMinimumHeight(windowHeight);
    }

    ~SplashWindow();


private:
    Ui::SplashWindow *ui;
};