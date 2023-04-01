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

    ui->p1XSlider->setValue(ui->openGLWidget->points[0].x * 10 + 50);
    ui->p1YSlider->setValue(ui->openGLWidget->points[0].y * 10 + 50);
    ui->p2XSlider->setValue(ui->openGLWidget->points[1].x * 10 + 50);
    ui->p2YSlider->setValue(ui->openGLWidget->points[1].y * 10 + 50);
    ui->p3XSlider->setValue(ui->openGLWidget->points[2].x * 10 + 50);
    ui->p3YSlider->setValue(ui->openGLWidget->points[2].y * 10 + 50);
    ui->p4XSlider->setValue(ui->openGLWidget->points[3].x * 10 + 50);
    ui->p4YSlider->setValue(ui->openGLWidget->points[3].y * 10 + 50);
    ui->p5XSlider->setValue(ui->openGLWidget->points[4].x * 10 + 50);
    ui->p5YSlider->setValue(ui->openGLWidget->points[4].y * 10 + 50);

    ui->p1Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[0].x) + ";" + std::to_string(ui->openGLWidget->points[0].y) + ")").c_str()));
    ui->p2Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[1].x) + ";" + std::to_string(ui->openGLWidget->points[1].y) + ")").c_str()));
    ui->p3Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[2].x) + ";" + std::to_string(ui->openGLWidget->points[2].y) + ")").c_str()));
    ui->p4Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[3].x) + ";" + std::to_string(ui->openGLWidget->points[3].y) + ")").c_str()));
    ui->p5Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[4].x) + ";" + std::to_string(ui->openGLWidget->points[4].y) + ")").c_str()));
}

void Lab4Widget::on_smoothBorderSlider_valueChanged(int value) {
    ui->openGLWidget->smoothBorder = double(value) / 5;
    ui->smoothBorderValue->setText(QString(std::to_string(ui->openGLWidget->smoothBorder).c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p1XSlider_valueChanged(int value) {
    ui->openGLWidget->points[0].x = double(value - 50) / 10;
    ui->p1XSlider->setValue(ui->openGLWidget->points[0].x * 10 + 50);
    ui->p1Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[0].x) + ";" + std::to_string(ui->openGLWidget->points[0].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p1YSlider_valueChanged(int value) {
    ui->openGLWidget->points[0].y = double(value - 50) / 10;
    ui->p1YSlider->setValue(ui->openGLWidget->points[0].y * 10 + 50);
    ui->p1Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[0].x) + ";" + std::to_string(ui->openGLWidget->points[0].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p2XSlider_valueChanged(int value) {
    ui->openGLWidget->points[1].x = double(value - 50) / 10;
    ui->p2XSlider->setValue(ui->openGLWidget->points[1].x * 10 + 50);
    ui->p2Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[1].x) + ";" + std::to_string(ui->openGLWidget->points[1].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p2YSlider_valueChanged(int value) {
    ui->openGLWidget->points[1].y = double(value - 50) / 10;
    ui->p2YSlider->setValue(ui->openGLWidget->points[1].y * 10 + 50);
    ui->p2Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[1].x) + ";" + std::to_string(ui->openGLWidget->points[1].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p3XSlider_valueChanged(int value) {
    ui->openGLWidget->points[2].x = double(value - 50) / 10;
    ui->p3XSlider->setValue(ui->openGLWidget->points[2].x * 10 + 50);
    ui->p3Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[2].x) + ";" + std::to_string(ui->openGLWidget->points[2].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p3YSlider_valueChanged(int value) {
    ui->openGLWidget->points[2].y = double(value - 50) / 10;
    ui->p3YSlider->setValue(ui->openGLWidget->points[2].y * 10 + 50);
    ui->p3Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[2].x) + ";" + std::to_string(ui->openGLWidget->points[2].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p4XSlider_valueChanged(int value) {
    ui->openGLWidget->points[3].x = double(value - 50) / 10;
    ui->p4XSlider->setValue(ui->openGLWidget->points[3].x * 10 + 50);
    ui->p4Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[3].x) + ";" + std::to_string(ui->openGLWidget->points[3].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p4YSlider_valueChanged(int value) {
    ui->openGLWidget->points[3].y = double(value - 50) / 10;
    ui->p4YSlider->setValue(ui->openGLWidget->points[3].y * 10 + 50);
    ui->p4Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[3].x) + ";" + std::to_string(ui->openGLWidget->points[3].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p5XSlider_valueChanged(int value) {
    ui->openGLWidget->points[4].x = double(value - 50) / 10;
    ui->p5XSlider->setValue(ui->openGLWidget->points[4].x * 10 + 50);
    ui->p5Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[4].x) + ";" + std::to_string(ui->openGLWidget->points[4].y) + ")").c_str()));
    ui->openGLWidget->update();
}

void Lab4Widget::on_p5YSlider_valueChanged(int value) {
    ui->openGLWidget->points[4].y = double(value - 50) / 10;
    ui->p5YSlider->setValue(ui->openGLWidget->points[4].y * 10 + 50);
    ui->p5Value->setText(QString(("(" + std::to_string(ui->openGLWidget->points[4].x) + ";" + std::to_string(ui->openGLWidget->points[4].y) + ")").c_str()));
    ui->openGLWidget->update();
}
