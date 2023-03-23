#include "lab3widget.h"

Lab3Widget::~Lab3Widget() {
    delete ui;
}

Lab3Widget::Lab3Widget(
        int windowWidth,
        int windowHeight,
        QWidget *parent
) : QWidget(parent), ui(new Ui::Lab3Widget) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void Lab3Widget::init(int windowWidth, int windowHeight) {
    setMinimumSize(windowWidth, windowHeight);
    setWindowTitle("Лабораторная работа №3");

    ui->openGLWidget->update();
    ui->deepSlider->setSliderPosition(0);
    ui->deepValue->setText(QString(std::to_string(ui->openGLWidget->deep).c_str()));
    ui->deltaXSlider->setSliderPosition(50);
    ui->deltaYSlider->setSliderPosition(50);
}

void Lab3Widget::on_deepSlider_valueChanged(int value) {
    ui->openGLWidget->deep = value / 10;
    ui->deepValue->setText(QString(std::to_string(ui->openGLWidget->deep).c_str()));
    ui->openGLWidget->update();
}

void Lab3Widget::on_deltaXSlider_valueChanged(int value) {
    ui->openGLWidget->xCenter = double(value) / 100 - 0.5;
    ui->deltaXValue->setText(QString(std::to_string(ui->openGLWidget->xCenter).c_str()));
    ui->openGLWidget->update();
}

void Lab3Widget::on_deltaYSlider_valueChanged(int value) {
    ui->openGLWidget->yCenter = double(value) / 100 - 0.5;
    ui->deltaYValue->setText(QString(std::to_string(ui->openGLWidget->yCenter).c_str()));
    ui->openGLWidget->update();
}
