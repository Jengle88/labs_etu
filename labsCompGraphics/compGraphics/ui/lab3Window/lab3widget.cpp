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
    ui->deltaXSlider->setSliderPosition(ui->openGLWidget->delta2X * 100);
    ui->deltaXLabel->setText(QString(std::to_string(ui->openGLWidget->delta2X * 100).c_str()));
    ui->deltaYSlider->setSliderPosition(ui->openGLWidget->delta2Y * 100);
    ui->deltaYLabel->setText(QString(std::to_string(ui->openGLWidget->delta2Y * 100).c_str()));
    ui->deltaXSlider2->setSliderPosition(int(ui->openGLWidget->delta2X * 10000) % 100);
    ui->deltaYSlider2->setSliderPosition(int(ui->openGLWidget->delta2Y * 10000) % 100);
}

void Lab3Widget::on_deltaXSlider_valueChanged(int value) {
    ui->openGLWidget->delta2X = double(value * 100 + int(ui->openGLWidget->delta2X * 10000) % 100) / 10000;
    ui->deltaXLabel->setText(QString(std::to_string(ui->openGLWidget->delta2X).c_str()));
    ui->openGLWidget->update();
}

void Lab3Widget::on_deltaYSlider_valueChanged(int value) {
    ui->openGLWidget->delta2Y = double(value * 100 + int(ui->openGLWidget->delta2Y * 10000) % 100) / 10000;
    ui->deltaYLabel->setText(QString(std::to_string(ui->openGLWidget->delta2Y).c_str()));
    ui->openGLWidget->update();
}


void Lab3Widget::on_deltaXSlider2_valueChanged(int value) {
    ui->openGLWidget->delta2X = double(int(ui->openGLWidget->delta2X * 100) * 100 + value) / 10000;
    ui->deltaXLabel->setText(QString(std::to_string(ui->openGLWidget->delta2X).c_str()));
    ui->openGLWidget->update();
}

void Lab3Widget::on_deltaYSlider2_valueChanged(int value) {
    ui->openGLWidget->delta2Y = double(int(ui->openGLWidget->delta2Y * 100) * 100 + value) / 10000;
    ui->deltaYLabel->setText(QString(std::to_string(ui->openGLWidget->delta2Y).c_str()));
    ui->openGLWidget->update();
}

