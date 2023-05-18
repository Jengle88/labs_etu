#include "lab6widget.h"
#include "ui_lab6widget.h"

Lab6Widget::~Lab6Widget() {
    delete ui;
}

Lab6Widget::Lab6Widget(
        int windowWidth,
        int windowHeight,
        QWidget *parent
) : QWidget(parent), ui(new Ui::Lab6Widget) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void Lab6Widget::init(int windowWidth, int windowHeight) {
    setMinimumSize(windowWidth, windowHeight);
    setWindowTitle("Лабораторная работа №6");
}

void Lab6Widget::on_resetCamera_clicked() {
    ui->openGLWidget->cameraPosition = {0, -2, -6};
    ui->openGLWidget->cameraRotation = {1, 0};
    ui->openGLWidget->cameraZoom = 0.85;

    ui->openGLWidget->update();
}
