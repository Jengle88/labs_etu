#include "lab1widget.h"

Lab1Widget::Lab1Widget(
        int windowWidth,
        int windowHeight,
        QWidget *parent
) : QWidget(parent), ui(new Ui::Lab1Widget) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void Lab1Widget::init(int windowWidth, int windowHeight) {
    setMinimumSize(windowWidth, windowHeight);
    setWindowTitle("Лабораторная работа №1");

    ui->selectPrimitive->insertItems(0, QStringList({"aba", "ewq", "asdq"}));

}

Lab1Widget::~Lab1Widget() {
    delete ui;
}

void Lab1Widget::on_selectPrimitive_activated(const QString &arg1) {

}
