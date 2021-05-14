#include <QLabel>
#include <iostream>
#include <utility>
#include "libs/mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

/* TODO:
 * 	1) Настроить доп окно для выбора характеристик квадрата --- V
 * 	2) Сделать перенос данных из доп окна в основное --- V
 * 	3) Добавить swap-файл для временного хранения изображения --- V
 * 	4) Добавить окно для RGB фильтра --- V
 * 	5) Сделать перенос данных из окна для RGB фильтра --- V
 * 	6) Добавить окно для поворота части изображения --- V
 * 	7) Добавить окно для рисования окружности --- V
 * 	8) Добавить окна для других функций --- V
 * 	9) Переделать структуры под Qt
 *
 * */


MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), ui(new Ui::MainWindow) {


	name_file = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.bmp");
	start_file = std::move(name_file);


	std::clog << "MainWindow created\n";
	ui->setupUi(this);

	this->squareForm = new CreateSquareForm(nullptr, &bmp_image);
	connect(squareForm, SIGNAL(send_results(bool)), this, SLOT(receiveEditedImage(bool)));
	squareForm->setFixedSize(380, 280);

	this->rgbFilterForm = new ChangeRGBFilterForm(nullptr, &bmp_image);
	connect(rgbFilterForm, SIGNAL(send_results(bool)), this, SLOT(receiveEditedImage(bool)));
	rgbFilterForm->setFixedSize(340, 210);

	this->rotateFragForm = new RotateFragmentForm(nullptr, &bmp_image);
	connect(rotateFragForm,SIGNAL(send_results(bool)), this, SLOT(receiveEditedImage(bool)));
	rotateFragForm->setFixedSize(450,250);

	this->drawCircleForm = new DrawCircleForm(nullptr, &bmp_image);
	connect(drawCircleForm,SIGNAL(send_results(bool)), this, SLOT(receiveEditedImage(bool)));
	drawCircleForm->setFixedSize(515,390);


	if(bmp_image.input_image(start_file.toStdString())){
		start_bmp_image = BMP(bmp_image);
		image = new QPixmap(start_file);
		*image = image->scaled(ui->label->width() - 2 * ui->label->margin(),
		                       ui->label->height() - 2 * ui->label->margin());
		ui->label->setPixmap(*image);
		ui->height_label->setText(QString::number(bmp_image.getHeight()));
		ui->width_label->setText(QString::number(bmp_image.getWidth()));
		ui->bit_pixels_label->setText(QString::number(bmp_image.getBitPerPixels()));
		ui->size_byte_label->setText(QString::number(bmp_image.getSize()));
	} else{
		ui->label->setText("Здесь могло быть ваше изображение!");
		QMessageBox::critical(this,"Attention!","Не удалось загрузить изображение!");
	}


	ui->label->setStyleSheet("QLabel {"
							 "border-style: solid;"
							 "border-width: 2px;"
							 "border-color: black; "
							 "}");
}

MainWindow::~MainWindow() {
	delete image;
	delete squareForm;
	delete rgbFilterForm;
	delete rotateFragForm;
	delete drawCircleForm;
	std::clog << "MainWindow finished\n";
	remove(".result.bmp");
	delete ui;
}
//SLOTs
void MainWindow::receiveNameImage(const QString& str) {
	this->name_file = str;
}

void MainWindow::receiveEditedImage(bool was_edited) {
	this->image_edited = was_edited;
}
//end SLOTs
void MainWindow::try_save() {
	if(this->image_edited){
		std::string s = ".result.bmp";
		bmp_image.write_bmp(s);
		delete image;
		image = new QPixmap(".result.bmp");
		*image = image->scaled(ui->label->width() - 2 * ui->label->margin(),
		                       ui->label->height() - 2 * ui->label->margin());
		ui->label->setPixmap(*image);
	}
	this->image_edited = false;
}

void MainWindow::on_draw_square_clicked()
{
	squareForm->init();
	squareForm->exec();
	try_save();
}

void MainWindow::on_change_RGB_clicked()
{
	rgbFilterForm->init();
	rgbFilterForm->exec();
	try_save();
}


void MainWindow::on_rotate_fragment_clicked()
{
	rotateFragForm->init();
	rotateFragForm->exec();
	try_save();
}

void MainWindow::on_draw_circle_clicked()
{
	drawCircleForm->init();
	drawCircleForm->exec();
	try_save();
}

void MainWindow::on_load_image_clicked()
{
	name_file = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.bmp");
	if (!name_file.isEmpty() && bmp_image.input_image(name_file.toStdString())){
		start_bmp_image = bmp_image;
		ui->height_label->setText(QString::number(bmp_image.getHeight()));
		ui->width_label->setText(QString::number(bmp_image.getWidth()));
		ui->bit_pixels_label->setText(QString::number(bmp_image.getBitPerPixels()));
		ui->size_byte_label->setText(QString::number(bmp_image.getSize()));
		delete image;
		image = new QPixmap(name_file);
		*image = image->scaled(ui->label->width() - 2 * ui->label->margin(),
		                       ui->label->height() - 2 * ui->label->margin());
		ui->label->setPixmap(*image);
	} else{
		QMessageBox::critical(this,"Attention!","Не удалось загрузить изображение!");
	}
}

void MainWindow::on_save_image_clicked()
{
	name_file = QFileDialog::getSaveFileName(nullptr, "Save Dialog", "", "*.bmp");
	if (!name_file.isEmpty())
		bmp_image.write_bmp(name_file.toStdString());
}

void MainWindow::on_reload_image_clicked()
{
	bmp_image = start_bmp_image;
	std::string s = ".result.bmp";
	bmp_image.write_bmp(s);
	delete image;
	image = new QPixmap(".result.bmp");
	*image = image->scaled(ui->label->width() - 2 * ui->label->margin(),
	                       ui->label->height() - 2 * ui->label->margin());
	ui->label->setPixmap(*image);
}



void MainWindow::on_pushButton_clicked()
{
	QMessageBox::information(this,"Информация",
		"Нарисовать квадрат: задаются координаты левого верхнего угла квадрата, его свойства и цвет. "
			"В дополнение также рисуются диагонали. При желании, квадрат можно залить внутри.\n\n"
		"Изменить RGB фильтр: выбрать одну из компонент (Красная, Зелёная, Синяя) и изменить её "
            "значение для всего изображения.\n\n"
		"Поворот части: выбрать координаты левого верхнего угла и правого нижнего угла фрагмента, а также "
            "угол поворота.\n\n"
		"Нарисовать окружность: окружность задаётся либо квадратом, в который она может быть вписана, либо центром и радиусом. "
            "Если выбран квадрат - задаются его верхний левый угол и правый нижний угол. Если выбран центр и радиус, "
			"то задаётся центр окружности и её радиус. Также есть возможность задать толщину, цвет линии и заливку.\n\n"
        "Загрузить изображение: выбрать другое изображение для обработки.\n\n"
		"Сохранить изображение: сохранить результат обработки в файл.\n\n"
        "Вернуться к исходному: отменить изменения и вернуть последнее загруженное изображение.\n\n"
		   );

}
