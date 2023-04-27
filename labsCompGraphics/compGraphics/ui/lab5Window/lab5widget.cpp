#include <QFileDialog>
#include <iostream>
#include "lab5widget.h"
#include "ui_lab5widget.h"

Lab5Widget::~Lab5Widget() {
    delete ui;
}

Lab5Widget::Lab5Widget(
        int windowWidth,
        int windowHeight,
        QWidget *parent
) : QWidget(parent), ui(new Ui::Lab5Widget) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void Lab5Widget::init(int windowWidth, int windowHeight) {
    setMinimumSize(windowWidth, windowHeight);
    setWindowTitle("Лабораторная работа №5");
    ui->deltaColorSlider->setMinimum(0);
    ui->deltaColorSlider->setMaximum(50);
    ui->deltaColorLabel->setText(QString(("Изменение цвета: " + std::to_string(ui->openGLWidget->deltaColor)).c_str()));
    ui->deltaPixelsSlider->setMinimum(0);
    ui->deltaPixelsSlider->setMaximum(50);
    ui->deltaPixelsLabel->setText(QString(("Расстояние между волнами: " + std::to_string(ui->openGLWidget->deltaPixels)).c_str()));
}

void Lab5Widget::on_chooseFile_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открытие файла"), "/",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    ui->imagePath->setText(fileName);
    ui->openGLWidget->imagePath = fileName;
    ui->openGLWidget->update();
}

void Lab5Widget::on_deltaPixelsSlider_valueChanged(int value) {
    ui->deltaPixelsLabel->setText(QString(("Расстояние между волнами: " + std::to_string(value)).c_str()));
    ui->openGLWidget->deltaPixels = value;
    ui->openGLWidget->update();
}

void Lab5Widget::on_deltaColorSlider_valueChanged(int value) {
    ui->deltaColorLabel->setText(QString(("Изменение цвета: " + std::to_string(value)).c_str()));
    ui->openGLWidget->deltaColor = value;
    ui->openGLWidget->update();
}
