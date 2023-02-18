#include "splashwindow.h"

SplashWindow::~SplashWindow() {
    delete lab1Widget;
    delete ui;
}
void SplashWindow::on_buttonLab1_clicked() {
    lab1Widget->show();
}

SplashWindow::SplashWindow(int windowWidth, int windowHeight, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::SplashWindow) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void SplashWindow::init(int windowWidth, int windowHeight) {
    lab1Widget = new Lab1Widget(windowWidth, windowHeight);
    setMinimumWidth(windowWidth);
    setMinimumHeight(windowHeight);
}
