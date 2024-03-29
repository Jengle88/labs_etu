#include "splashwindow.h"
#include "ui/lab3Window/lab3widget.h"
#include "ui/lab4Window/lab4widget.h"

SplashWindow::SplashWindow(int windowWidth, int windowHeight, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::SplashWindow) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void SplashWindow::init(int windowWidth, int windowHeight) {
    this->setWindowTitle("Компьютерная графика. Шквиря Е.В.");
    lab1Widget = new Lab1Widget(windowWidth, windowHeight);
    lab2Widget = new Lab2Widget(windowWidth, windowHeight);
    lab3Widget = new Lab3Widget(windowWidth, windowHeight);
    lab4Widget = new Lab4Widget(windowWidth, windowHeight);
    lab5Widget = new Lab5Widget(windowWidth, windowHeight);
    lab6Widget = new Lab6Widget(std::max(windowWidth, windowHeight),
                                std::max(windowWidth, windowHeight));
    setMinimumWidth(windowWidth);
    setMinimumHeight(windowHeight);
}

void SplashWindow::on_buttonLab1_clicked() {
    safeShowWidget(lab1Widget);
}

void SplashWindow::on_buttonLab2_clicked() {
    safeShowWidget(lab2Widget);
}

void SplashWindow::on_buttonLab3_clicked() {
    safeShowWidget(lab3Widget);
}

void SplashWindow::on_buttonLab4_clicked() {
    safeShowWidget(lab4Widget);
}


void SplashWindow::on_buttonLab5_clicked() {
    safeShowWidget(lab5Widget);
}

void SplashWindow::on_buttonLab6_clicked() {
    safeShowWidget(lab6Widget);
}

SplashWindow::~SplashWindow() {
    delete lab1Widget;
    delete lab2Widget;
    delete lab3Widget;
    delete lab4Widget;
    delete lab5Widget;
    delete lab6Widget;
    delete ui;
}

void SplashWindow::safeShowWidget(QWidget *widget) {
    if (lab1Widget != widget)
        lab1Widget->hide();
    if (lab2Widget != widget)
        lab2Widget->hide();
    if (lab3Widget != widget)
        lab3Widget->hide();
    if (lab4Widget != widget)
        lab4Widget->hide();
    if (lab5Widget != widget)
        lab5Widget->hide();
    if (lab6Widget != widget)
        lab6Widget->hide();

    widget->show();
}
