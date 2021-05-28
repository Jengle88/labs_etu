#include <QMessageBox>
#include "libs/makeframeform.h"

MakeFrameForm::MakeFrameForm(QWidget *parent, BMP *bmp_image) :
    QDialog(parent),
    ui(new Ui::MakeFrameForm)
{
    ui->setupUi(this);
	this->bmp_image = bmp_image;
	std::clog << "MakeFrameForm created\n";
}

MakeFrameForm::~MakeFrameForm()
{
    delete ui;
}

void MakeFrameForm::init() {
	ui->line_width->setText("");
	ui->rcolor->setText("");
	ui->gcolor->setText("");
	ui->bcolor->setText("");
}

void MakeFrameForm::on_buttonBox_accepted() {
	bool check[5] = {false};
	int line_width = ui->line_width->text().toInt(&check[0]);
	int r = ui->rcolor->text().toInt(&check[1]);
	int g = ui->gcolor->text().toInt(&check[2]);
	int b = ui->bcolor->text().toInt(&check[3]);
	check[4] = ColorItem::is_correct_color(b, g, r, 0);
	ColorItem line_color = ColorItem(b, g, r, 0);
	bool res = true;
	for (bool arr_ok : check) {
		res &= arr_ok;
	}
	if (!res || !bmp_image->make_frame(line_width,line_color))
		QMessageBox::warning(this, "Ошибка", "Некоторые параметры указаны неверно!");
	else {
		emit send_result(true);
		std::clog << "Result MakeFrameForm sent\n";
		close();
	}
}

void MakeFrameForm::on_buttonBox_rejected() {
	std::clog << "Edit canceled\n";
	close();
}