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
}

void Lab1Widget::loadListOfNamePrimitives() {
    QStringList listOfNamePrimitives;
    listOfNamePrimitives.reserve(lab1Primitives.getNameOfPrimitives().size());
    for (const auto &name: lab1Primitives.getNameOfPrimitives()) listOfNamePrimitives.append(name);
    ui->selectPrimitive->addItems(listOfNamePrimitives);
}

void Lab1Widget::on_selectPrimitive_currentIndexChanged(const QString &newPrimitive) {

}

Lab1Widget::~Lab1Widget() {
    delete ui;
}
