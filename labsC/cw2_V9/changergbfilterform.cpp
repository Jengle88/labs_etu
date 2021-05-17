#include "libs/changergbfilterform.h"

ChangeRGBFilterForm::ChangeRGBFilterForm(QWidget *parent, BMP *bmp_image) :
		QDialog(parent),
		ui(new Ui::ChangeRGBFilterForm)
{
	ui->setupUi(this);
	this->bmp_image = bmp_image;
	this->was_edited = false;
	ui->rComponent->setChecked(true);
	std::clog << "ChangeRGBFilterForm created\n";
}

ChangeRGBFilterForm::~ChangeRGBFilterForm()
{
	delete ui;
	std::clog << "ChangeRGBFilterForm deleted\n";
}

void ChangeRGBFilterForm::init() {
	ui->rComponent->setChecked(true);
	ui->newComponent->setText("0");
	std::clog << "ChangeRGBFilterForm initialized\n";
}


void ChangeRGBFilterForm::on_buttonBox_accepted()
{
	bool rightNum = false;
	int num = ui->newComponent->text().toInt(&rightNum);
	char component = '$';
	if(ui->rComponent->isChecked())
		component = 'r';
	else if(ui->gComponent->isChecked())
		component = 'g';
	else if(ui->bComponent->isChecked())
		component = 'b';
	if(!rightNum || !bmp_image->edit_component(component, num)) {
		QMessageBox::warning(this,"Attention!","Некоторые параметры указаны неверно!");
	} else {
		this->was_edited = true;
		emit send_results(was_edited);
		std::clog << "Component edited\n";
		close();
	}
}

void ChangeRGBFilterForm::on_buttonBox_rejected()
{
	std::clog << "Edit canceled\n";
	close();
}
