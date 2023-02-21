#include "lab2widget.h"
#include "ui_lab2widget.h"

Lab2Widget::Lab2Widget(
        int windowWidth,
        int windowHeight,
        QWidget *parent
) : QWidget(parent), ui(new Ui::Lab2Widget) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

void Lab2Widget::init(int windowWidth, int windowHeight) {
    setMinimumSize(windowWidth, windowHeight);
    setWindowTitle("Лабораторная работа №2");

    loadListOfNamePrimitives();
    setDropdownMenuOfPrimitives();
}

void Lab2Widget::setDropdownMenuOfPrimitives() {
    ui->selectPrimitive->addItems(listOfNamePrimitives);
    ui->selectPrimitive->setCurrentIndex(0);
}

void Lab2Widget::loadListOfNamePrimitives() {
    listOfNamePrimitives.reserve(Lab1Primitives::getNameOfPrimitives().size());
    for (const auto &name: Lab1Primitives::getNameOfPrimitives()) listOfNamePrimitives.append(name);
}

void Lab2Widget::on_selectPrimitive_currentIndexChanged(const QString &newPrimitive) {
    ui->openGLWidget->setFigure(newPrimitive);
}

Lab2Widget::~Lab2Widget() {
    delete ui;
}
