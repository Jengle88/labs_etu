#include <QMessageBox>
#include "libs/drawcircleform.h"

DrawCircleForm::DrawCircleForm(QWidget *parent, BMP *bmp_image) :
    QDialog(parent),
    ui(new Ui::DrawCircleForm)
{
	std::clog << "DrawCircleForm created\n";
	this->bmp_image = bmp_image;
	this->was_edited = false;
	ui->setupUi(this);
}

DrawCircleForm::~DrawCircleForm()
{
	std::clog << "DrawCircleForm deleted\n";
	delete ui;
}

void DrawCircleForm::init() {
	ui->drawSquare->setChecked(true);
	ui->drawPointRad->setChecked(false);
	ui->xlpos->setEnabled(true);
	ui->ylpos->setEnabled(true);
	ui->xrpos->setEnabled(true);
	ui->yrpos->setEnabled(true);
	ui->xcenter->setEnabled(false);
	ui->ycenter->setEnabled(false);
	ui->radius->setEnabled(false);
	ui->xlpos->clear();
	ui->ylpos->clear();
	ui->xrpos->clear();
	ui->yrpos->clear();
	ui->xcenter->clear();
	ui->ycenter->clear();
	ui->radius->clear();
	ui->line_width->setText("1");
	ui->line_r->setText("0");
	ui->line_g->setText("0");
	ui->line_b->setText("0");
	ui->is_pure_over->setCheckState(Qt::Unchecked);
	ui->over_b->setEnabled(false);
	ui->over_g->setEnabled(false);
	ui->over_r->setEnabled(false);
	ui->over_r->setText("0");
	ui->over_g->setText("0");
	ui->over_b->setText("0");
}
void DrawCircleForm::on_buttonBox_accepted()
{
	if(ui->drawSquare->isChecked()){
		bool check[11] = {false};
		int _xlpos = ui->xlpos->text().toInt(&check[0]);
		int _ylpos = ui->ylpos->text().toInt(&check[1]);
		int _xrpos = ui->xrpos->text().toInt(&check[2]);
		int _yrpos = ui->yrpos->text().toInt(&check[3]);
		int _line_width = ui->line_width->text().toInt(&check[4]);
		int _r = ui->line_r->text().toInt(&check[5]);
		int _g = ui->line_g->text().toInt(&check[6]);
		int _b = ui->line_b->text().toInt(&check[7]);
		check[5] = check[6] = check[7] = ColorItem::is_correct_color(_b, _g, _r, 0);
		ColorItem _line_color = ColorItem(_b,_g,_r, 0);
		_r = ui->over_r->text().toInt(&check[8]);
		_g = ui->over_g->text().toInt(&check[9]);
		_b = ui->over_b->text().toInt(&check[10]);
		if(ui->is_pure_over->isChecked()){
			check[8] = check[9] = check[10] = ColorItem::is_correct_color(_b, _g, _r, 0);
		} else{
			check[8] = check[9] = check[10] = true;
		}
		ColorItem _over_color = ColorItem(_b, _g, _r, 0);
		bool res = true;
		for (bool arr_ok : check) {
			res &= arr_ok;
		}
		if(!res || !bmp_image->draw_circle_via_square(_xlpos, _ylpos, _xrpos, _yrpos,_line_width, _line_color,
											   ui->is_pure_over->isChecked(),  _over_color)){
			QMessageBox::warning(this,"Attention!","Некоторые параметры указаны неверно!");
		} else{
			this->was_edited = true;
			std::clog << "Result sent\n";
			emit send_results(was_edited);
			close();
		}
	} else {
		bool check[10] = {false};
		int _xcenter = ui->xcenter->text().toInt(&check[0]);
		int _ycenter = ui->ycenter->text().toInt(&check[1]);
		int _radius = ui->radius->text().toInt(&check[2]);
		int _line_width = ui->line_width->text().toInt(&check[3]);
		int _r = ui->line_r->text().toInt(&check[4]);
		int _g = ui->line_g->text().toInt(&check[5]);
		int _b = ui->line_b->text().toInt(&check[6]);
		check[5] = check[6] = check[7] = ColorItem::is_correct_color(_b, _g, _r, 0);
		ColorItem _line_color = ColorItem(_b,_g,_r, 0);
		_r = ui->over_r->text().toInt(&check[7]);
		_g = ui->over_g->text().toInt(&check[8]);
		_b = ui->over_b->text().toInt(&check[9]);
		if(ui->is_pure_over->isChecked()){
			check[7] = check[8] = check[9] = ColorItem::is_correct_color(_b, _g, _r, 0);
		} else{
			check[7] = check[8] = check[9] = true;
		}
		ColorItem _over_color = ColorItem(_b, _g, _r, 0);
		bool res = true;
		for (bool arr_ok : check) {
			res &= arr_ok;
		}
		if(!res || !bmp_image->draw_circle_via_radius(_xcenter, _ycenter, _radius,_line_width, _line_color,
		                                             ui->is_pure_over->isChecked(),  _over_color)){
			QMessageBox::warning(this,"Attention!","Некоторые параметры указаны неверно!");
		} else {
			this->was_edited = true;
			std::clog << "Result sent\n";
			emit send_results(was_edited);
			close();
		}
	}

}

void DrawCircleForm::on_buttonBox_rejected()
{
	std::clog << "Edit canceled\n";
	close();
}

void DrawCircleForm::on_drawSquare_clicked()
{
	ui->xlpos->setEnabled(true);
	ui->ylpos->setEnabled(true);
	ui->xrpos->setEnabled(true);
	ui->yrpos->setEnabled(true);
	ui->xcenter->setEnabled(false);
	ui->ycenter->setEnabled(false);
	ui->radius->setEnabled(false);
}

void DrawCircleForm::on_drawPointRad_clicked()
{
	ui->xlpos->setEnabled(false);
	ui->ylpos->setEnabled(false);
	ui->xrpos->setEnabled(false);
	ui->yrpos->setEnabled(false);
	ui->xcenter->setEnabled(true);
	ui->ycenter->setEnabled(true);
	ui->radius->setEnabled(true);
}

void DrawCircleForm::on_is_pure_over_stateChanged(int arg1)
{
	if(ui->is_pure_over->isChecked()){
		ui->over_r->setEnabled(true);
		ui->over_g->setEnabled(true);
		ui->over_b->setEnabled(true);
	} else {
		ui->over_r->setEnabled(false);
		ui->over_g->setEnabled(false);
		ui->over_b->setEnabled(false);
	}
}
