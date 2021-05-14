#include "libs/opensaveimageform.h"

OpenSaveImageForm::OpenSaveImageForm(QWidget *parent, bool save_form) :
    QDialog(parent),
    ui(new Ui::OpenSaveImageForm),
    save_form(save_form)
{
    ui->setupUi(this);
    std::clog << "OpenSaveImageForm created\n";
}

OpenSaveImageForm::~OpenSaveImageForm()
{
	std::clog << "OpenSaveImageForm deleted\n";
    delete ui;
}


void OpenSaveImageForm::on_accept_clicked()
{
	if(!save_form) {
		if (fopen(ui->name_file->text().toStdString().c_str(), "r") != nullptr) {
			emit sendData(ui->name_file->text());
			close();
		}
		else {
			ui->label_2->setText("Файл не найден!");
		}
	} else{
		emit sendData(ui->name_file->text());
		close();
	}
}

void OpenSaveImageForm::init() {
	ui->name_file->clear();
	ui->label_2->clear();
}
