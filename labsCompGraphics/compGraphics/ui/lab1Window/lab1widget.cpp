#include "lab1widget.h"
#include "ui/openGLWidget/OpenGLWidget.h"

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

    loadListOfNamePrimitives();
    setDropdownMenuOfPrimitives();
}

void Lab1Widget::setDropdownMenuOfPrimitives() {
    ui->selectPrimitive->addItems(listOfNamePrimitives);
    ui->selectPrimitive->setCurrentIndex(0);
}

void Lab1Widget::loadListOfNamePrimitives() {
    listOfNamePrimitives.reserve(Lab1Primitives::getNameOfPrimitives().size());
    for (const auto &name: Lab1Primitives::getNameOfPrimitives()) listOfNamePrimitives.append(name);
}

void Lab1Widget::on_selectPrimitive_currentIndexChanged(const QString &newPrimitive) {
    ui->openGLWidget->update(newPrimitive);
}

Lab1Widget::~Lab1Widget() {
    delete ui;
}
