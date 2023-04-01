#include "lab4widget.h"


Lab4Widget::~Lab4Widget() {
    delete ui;
}

Lab4Widget::Lab4Widget(
        int windowWidth,
        int windowHeight,
        QWidget *parent
) : QWidget(parent), ui(new Ui::Lab4Widget) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void Lab4Widget::init(int windowWidth, int windowHeight) {
    setMinimumSize(windowWidth, windowHeight);
    setWindowTitle("Лабораторная работа №4");


    ui->openGLWidget->update();
    ui->smoothBorderSlider->setSliderPosition(2);
    ui->smoothBorderSlider->setMaximum(100);
    ui->smoothBorderValue->setText(QString(std::to_string(ui->openGLWidget->smoothBorder).c_str()));
}

void Lab4Widget::on_smoothBorderSlider_valueChanged(int value) {
    ui->openGLWidget->smoothBorder = double(value) / 5;
    ui->smoothBorderValue->setText(QString(std::to_string(ui->openGLWidget->smoothBorder).c_str()));
    ui->openGLWidget->update();
}
