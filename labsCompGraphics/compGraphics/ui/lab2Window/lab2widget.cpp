#include "lab2widget.h"

Lab2Widget::Lab2Widget(
        int windowWidth,
        int windowHeight,
        QWidget *parent
) : QWidget(parent), ui(new Ui::Lab2Widget) {
    ui->setupUi(this);
    init(windowWidth, windowHeight);
}

Lab2Widget::~Lab2Widget() {
    delete ui;
}

void Lab2Widget::init(int windowWidth, int windowHeight) {
    setMinimumSize(windowWidth, windowHeight);
    setWindowTitle("Лабораторная работа №2");

    setQComboBoxMenu(vectorOfQStringToQStringList(Lab1Primitives::getNameOfPrimitives()), ui->selectPrimitive);
    setQComboBoxMenu(vectorOfQStringToQStringList(Lab2Primitives::getNamesOfAlphaFunc()), ui->alphaFuncSelect);
    setQComboBoxMenu(vectorOfQStringToQStringList(Lab2Primitives::getNamesOfBlendFuncSFactor()),
                     ui->blendSFactorSelect);
    setQComboBoxMenu(vectorOfQStringToQStringList(Lab2Primitives::getNamesOfBlendFuncDFactor()),
                     ui->blendDFactorSelect);

    ui->xSlider->setSliderPosition(0);
    ui->ySlider->setSliderPosition(0);
    ui->widthSlider->setSliderPosition(100);
    ui->heightSlider->setSliderPosition(100);
}

QStringList Lab2Widget::vectorOfQStringToQStringList(const QList<QString> &src) {
    QStringList tempList;
    tempList.reserve(src.size());
    for (const auto &name: src) tempList.append(name);
    return tempList;
}

void Lab2Widget::setQComboBoxMenu(const QStringList &listOfItems, QComboBox *qComboBox) {
    qComboBox->addItems(listOfItems);
    qComboBox->setCurrentIndex(0);
}

void Lab2Widget::updateOpenGLWidgetState() {

    double x = ui->xSlider->sliderPosition() / 100.;
    double y = ui->ySlider->sliderPosition() / 100.;
    double width = ui->widthSlider->sliderPosition() / 100.;
    double height = ui->heightSlider->sliderPosition() / 100.;
    ui->openGLWidget->setScissorParams(ui->scissorEnable->isChecked(), x, y, width, height);

    QString alphaFunc = ui->alphaFuncSelect->currentText();
    double alphaFuncValue = ui->alphaFuncSlider->sliderPosition() / 100.;
    ui->openGLWidget->setAlphaParams(ui->alphaFuncEnable->isChecked(),
                                     alphaFunc, alphaFuncValue);

    QString sFactor = ui->blendSFactorSelect->currentText();
    QString dFactor = ui->blendDFactorSelect->currentText();
    ui->openGLWidget->setBlendFactorParams(ui->blendFuncEnable->isChecked(), sFactor, dFactor);

    ui->openGLWidget->setFigure(ui->selectPrimitive->currentText());
}

void Lab2Widget::on_selectPrimitive_currentIndexChanged(const QString &newPrimitive) {
    ui->openGLWidget->setFigure(newPrimitive);
}

void Lab2Widget::on_scissorEnable_clicked() {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_alphaFuncEnable_clicked() {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_blendFuncEnable_clicked() {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_xSlider_valueChanged(int value) {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_ySlider_valueChanged(int value) {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_widthSlider_valueChanged(int value) {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_heightSlider_valueChanged(int value) {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_alphaFuncSelect_currentIndexChanged(const QString &arg1) {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_alphaFuncSlider_valueChanged(int value) {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_blendSFactorSelect_currentIndexChanged(const QString &arg1) {
    updateOpenGLWidgetState();
}

void Lab2Widget::on_blendDFactorSelect_currentIndexChanged(const QString &arg1) {
    updateOpenGLWidgetState();
}
