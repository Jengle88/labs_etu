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
    ui->doubleSpinBox->setSingleStep(0.1);
    ui->doubleSpinBox_2->setSingleStep(0.1);
    ui->doubleSpinBox_3->setSingleStep(0.1);
    ui->doubleSpinBox_4->setSingleStep(0.1);
    ui->doubleSpinBox_5->setSingleStep(0.1);
    ui->doubleSpinBox_6->setSingleStep(0.1);
}

void Lab6Widget::on_doubleSpinBox_valueChanged(double arg1) {
    ui->openGLWidget->scx = arg1;
    ui->openGLWidget->update();
}

void Lab6Widget::on_doubleSpinBox_2_valueChanged(double arg1) {
    ui->openGLWidget->scy = arg1;
    ui->openGLWidget->update();
}

void Lab6Widget::on_doubleSpinBox_3_valueChanged(double arg1) {
    ui->openGLWidget->scz = arg1;
    ui->openGLWidget->update();
}

void Lab6Widget::on_doubleSpinBox_4_valueChanged(double arg1) {
    ui->openGLWidget->hpa = arg1;
    ui->openGLWidget->update();
}

void Lab6Widget::on_doubleSpinBox_5_valueChanged(double arg1) {
    ui->openGLWidget->hpb = arg1;
    ui->openGLWidget->update();
}

void Lab6Widget::on_doubleSpinBox_6_valueChanged(double arg1) {
    ui->openGLWidget->hpc = arg1;
    ui->openGLWidget->update();
}
