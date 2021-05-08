#include <QMessageBox>
#include "libs/rotatefragmentform.h"

RotateFragmentForm::RotateFragmentForm(QWidget *parent, BMP *bmp_image) :
    QDialog(parent),
    ui(new Ui::RotateFragmentForm)
{
	std::clog << "RotateFragmentForm created\n";
	this->bmp_image = bmp_image;
	this->was_edited = false;
	ui->setupUi(this);
}

RotateFragmentForm::~RotateFragmentForm()
{
	std::clog << "RotateFragmentForm deleted\n";
	delete ui;
}

void RotateFragmentForm::init() {
	ui->angle90->setChecked(true);
	ui->angle180->setChecked(false);
	ui->angle270->setChecked(false);
	ui->xlpos->setText(QString::fromStdString(""));
	ui->ylpos->setText(QString::fromStdString(""));
	ui->xrpos->setText(QString::fromStdString(""));
	ui->yrpos->setText(QString::fromStdString(""));
}

void RotateFragmentForm::on_buttonBox_accepted()
{

	int angle = 90;
	if(ui->angle90->isChecked())
		angle = 90;
	else if(ui->angle180->isChecked())
		angle = 180;
	else if(ui->angle270->isChecked())
		angle = 270;
	bool check[4] = {false};
	int xlpos = ui->xlpos->text().toInt(&check[0]);
	int ylpos = ui->ylpos->text().toInt(&check[1]);
	int xrpos = ui->xrpos->text().toInt(&check[2]);
	int yrpos = ui->yrpos->text().toInt(&check[3]);
	if(!(check[0] & check[1] & check[2] & check[3]) || !bmp_image->rotate_fragment(xlpos, ylpos,
																			   xrpos, yrpos, angle))
	{
		QMessageBox::warning(this,"Attention!","Некоторые параметры указаны неверно!");
	} else{
		this->was_edited = true;
		std::clog << "Fragment rotated\n";
		emit send_results(was_edited);
		close();
	}
//	if(!bmp_image->rotate_fragment(component, num)) {
//		QMessageBox::warning(this,"Attention!","Некоторые параметры указаны неверно!");
//	} else {
//		this->was_edited = true;
//		std::clog << "Component edited\n";
//		emit send_results(was_edited);
//		close();
//	}
}

void RotateFragmentForm::on_buttonBox_rejected()
{
	close();
}
