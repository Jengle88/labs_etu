#include "libs/createsquareform.h"


CreateSquareForm::CreateSquareForm(QWidget *parent, BMP *bmp_image) :
		QDialog(parent),
		ui(new Ui::CreateSquareForm) {
	this->bmp_image = bmp_image;
	ui->setupUi(this);
	std::clog << "CreateSquareForm created\n";
}

CreateSquareForm::~CreateSquareForm() {
	delete ui;
	std::clog << "CreateSquareForm deleted\n";
}

void CreateSquareForm::init() {
	ui->xpos->clear();
	ui->ypos->clear();
	ui->line_length->setText("2");
	ui->line_width->setText("1");
	line_set_color(CLR_BLACK);
	ui->is_pure_over->setCheckState(Qt::Unchecked);
	ui->over_b->setEnabled(false);
	ui->over_g->setEnabled(false);
	ui->over_r->setEnabled(false);
	over_set_color(CLR_BLACK);
	std::clog << "CreateSquareForm initialized\n";
}

void CreateSquareForm::on_buttonBox_accepted() {
	bool check[12] = {false};
	int xpos = ui->xpos->text().toInt(&check[0]);
	int ypos = ui->ypos->text().toInt(&check[1]);
	int line_length = ui->line_length->text().toInt(&check[2]);
	int line_width = ui->line_width->text().toInt(&check[3]);
	int b = ui->line_b->text().toInt(&check[4]);
	int g = ui->line_g->text().toInt(&check[5]);
	int r = ui->line_r->text().toInt(&check[6]);
	check[7] = ColorItem::is_correct_color(b, g, r, 0);
	ColorItem line_color = ColorItem(b, g, r, 0);
	bool is_pure_over = ui->is_pure_over->isChecked();
	ColorItem pure_over_color;
	if (is_pure_over) {
		b = ui->over_b->text().toInt(&check[8]);
		g = ui->over_g->text().toInt(&check[9]);
		r = ui->over_r->text().toInt(&check[10]);
		check[11] = ColorItem::is_correct_color(b, g, r, 0);
		pure_over_color = ColorItem(b, g, r, 0);
	}
	else {
		check[11] = true;
	}

	bool res = true;
	for (bool arr_ok : check) {
		res &= arr_ok;
	}
	if (!res || !bmp_image->draw_square(xpos, ypos, line_length, line_width, line_color, is_pure_over,
	                                    pure_over_color))
		QMessageBox::warning(this, "Ошибка", "Некоторые параметры указаны неверно!");
	else {
		emit send_result(true);
		std::clog << "Result CreateSquareForm sent\n";
		close();
	}
}

void CreateSquareForm::on_is_pure_over_stateChanged(int arg1) {
	if (ui->is_pure_over->isChecked()) {
		ui->over_b->setEnabled(true);
		ui->over_g->setEnabled(true);
		ui->over_r->setEnabled(true);
	}
	else {
		ui->over_b->setEnabled(false);
		ui->over_g->setEnabled(false);
		ui->over_r->setEnabled(false);
	}
}


void CreateSquareForm::on_buttonBox_rejected() {
	std::clog << "Edit canceled\n";
	close();
}


void CreateSquareForm::line_set_color(ColorItem color) {
	ui->line_r->setText(QString::number(color.Red));
	ui->line_g->setText(QString::number(color.Green));
	ui->line_b->setText(QString::number(color.Blue));
}

void CreateSquareForm::over_set_color(ColorItem color) {
	ui->over_r->setText(QString::number(color.Red));
	ui->over_g->setText(QString::number(color.Green));
	ui->over_b->setText(QString::number(color.Blue));
}

void CreateSquareForm::on_line_black_clicked() {
	line_set_color(CLR_BLACK);
}
void CreateSquareForm::on_line_white_clicked() {
	line_set_color(CLR_WHITE);
}
void CreateSquareForm::on_line_red_clicked() {
	line_set_color(CLR_RED);
}
void CreateSquareForm::on_line_green_clicked() {
	line_set_color(CLR_GREEN);
}
void CreateSquareForm::on_line_blue_clicked() {
	line_set_color(CLR_BLUE);
}
void CreateSquareForm::on_line_yellow_clicked() {
	line_set_color(CLR_YELLOW);
}
void CreateSquareForm::on_line_pink_clicked() {
	line_set_color(CLR_PINK);
}
void CreateSquareForm::on_line_orange_clicked() {
	line_set_color(CLR_ORANGE);
}
void CreateSquareForm::on_over_black_clicked() {
	over_set_color(CLR_BLACK);
}
void CreateSquareForm::on_over_white_clicked() {
	over_set_color(CLR_WHITE);
}
void CreateSquareForm::on_over_red_clicked() {
	over_set_color(CLR_RED);
}
void CreateSquareForm::on_over_green_clicked() {
	over_set_color(CLR_GREEN);
}
void CreateSquareForm::on_over_blue_clicked() {
	over_set_color(CLR_BLUE);
}
void CreateSquareForm::on_over_yellow_clicked() {
	over_set_color(CLR_YELLOW);
}
void CreateSquareForm::on_over_pink_clicked() {
	over_set_color(CLR_PINK);
}
void CreateSquareForm::on_over_orange_clicked() {
	over_set_color(CLR_ORANGE);
}




