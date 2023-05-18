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

    ui->globalScaleSlider->setSliderPosition(20);
    ui->globalScaleLabel->setText(QString(("Общее масштабирование: " + std::to_string(ui->openGLWidget->globalScale)).c_str()));
}

void Lab6Widget::on_resetCamera_clicked() {
    ui->openGLWidget->cameraPosition = {0, -2, -6};
    ui->openGLWidget->cameraRotation = {1, 0};
    ui->openGLWidget->cameraZoom = 0.85;

    ui->openGLWidget->update();
}

void Lab6Widget::on_globalScaleSlider_valueChanged(int value) {
    ui->openGLWidget->globalScale = double(value) / 20;
    ui->globalScaleLabel->setText(QString(("Общее масштабирование: " + std::to_string(ui->openGLWidget->globalScale)).c_str()));
    ui->openGLWidget->update();
}
