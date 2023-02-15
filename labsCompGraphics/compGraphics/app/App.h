#pragma once
//
// Created by evgeny on 16.02.23.
//

#include <QApplication>
#include "ui/splashWindow/splashwindow.h"

class App {
public:
    static int windowWidth;
    static int windowHeight;

    static int start(int argc, char *argv[]);
};

int App::windowWidth = 800;
int App::windowHeight = 600;

int App::start(int argc, char **argv) {
    QApplication a(argc, argv);
    SplashWindow w(windowWidth, windowHeight);
    w.show();

    return a.exec();
}
