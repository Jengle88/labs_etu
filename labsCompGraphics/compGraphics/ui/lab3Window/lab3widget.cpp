#include "lab3widget.h"

Lab3Widget::~Lab3Widget()
{
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
}
