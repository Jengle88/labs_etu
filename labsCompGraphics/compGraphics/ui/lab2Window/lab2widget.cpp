#include "lab2widget.h"
#include "ui_lab2widget.h"
#include "labs/lab2/Lab2Primitives.h"

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

    setQComboBoxMenu(vectorOfQStringToQStringList(Lab1Primitives::getNameOfPrimitives()), ui->selectPrimitive);
    setQComboBoxMenu(vectorOfQStringToQStringList(Lab2Primitives::getNamesOfAlphaFunc()), ui->alphaFuncSelect);
    setQComboBoxMenu(vectorOfQStringToQStringList(Lab2Primitives::getNamesOfBlendFuncSFactor()), ui->blendSFactorSelect);
    setQComboBoxMenu(vectorOfQStringToQStringList(Lab2Primitives::getNamesOfBlendFuncDFactor()), ui->blendDFactorSelect);
}

void Lab2Widget::on_selectPrimitive_currentIndexChanged(const QString &newPrimitive) {
    ui->openGLWidget->setFigure(newPrimitive);
}

QStringList Lab2Widget::vectorOfQStringToQStringList(const std::vector<QString> &src) {
    QStringList tempList;
    tempList.reserve(src.size());
    for (const auto &name: src) tempList.append(name);
    return tempList;
}

void Lab2Widget::setQComboBoxMenu(const QStringList &listOfItems, QComboBox *qComboBox) {
    qComboBox->addItems(listOfItems);
    qComboBox->setCurrentIndex(0);
}

Lab2Widget::~Lab2Widget() {
    delete ui;
}
