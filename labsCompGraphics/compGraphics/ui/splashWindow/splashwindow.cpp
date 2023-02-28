#include "splashwindow.h"

SplashWindow::SplashWindow(int windowWidth, int windowHeight, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::SplashWindow) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void SplashWindow::init(int windowWidth, int windowHeight) {
    this->setWindowTitle("Компьютерная графика. Шквиря Е.В.");
    lab1Widget = new Lab1Widget(windowWidth, windowHeight);
    lab2Widget = new Lab2Widget(windowWidth, windowHeight);
    setMinimumWidth(windowWidth);
    setMinimumHeight(windowHeight);
}

void SplashWindow::on_buttonLab1_clicked() {
    safeShowWidget(lab1Widget);
}

void SplashWindow::on_buttonLab2_clicked() {
    safeShowWidget(lab2Widget);
}

SplashWindow::~SplashWindow() {
    delete lab1Widget;
    delete lab2Widget;
    delete ui;
}

void SplashWindow::safeShowWidget(QWidget *widget) {
    if (lab1Widget != widget)
        lab1Widget->hide();
    if (lab2Widget != widget)
        lab2Widget->hide();

    widget->show();
}
