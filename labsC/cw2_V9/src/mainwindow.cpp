#include <QLabel>
#include <iostream>
#include "libs/mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), ui(new Ui::MainWindow) {

	//получение имени файла
	name_file = QFileDialog::getOpenFileName(nullptr, "Открытие файла", "", "*.bmp");

	std::clog << "MainWindow created\n";
	ui->setupUi(this);

	//создание форм для функций
	this->squareForm = new CreateSquareForm(nullptr, &bmp_image);
	connect(squareForm, &CreateSquareForm::send_result, this, &MainWindow::receive_flag_edited_image);
	squareForm->setFixedSize(460, 370);

	this->rgbFilterForm = new ChangeRGBFilterForm(nullptr, &bmp_image);
	connect(rgbFilterForm, &ChangeRGBFilterForm::send_result, this, &MainWindow::receive_flag_edited_image);
	rgbFilterForm->setFixedSize(340, 210);

	this->rotateFragForm = new RotateFragmentForm(nullptr, &bmp_image);
	connect(rotateFragForm, &RotateFragmentForm::send_result, this, &MainWindow::receive_flag_edited_image);
	rotateFragForm->setFixedSize(440, 250);

	this->drawCircleForm = new DrawCircleForm(nullptr, &bmp_image);
	connect(drawCircleForm, &DrawCircleForm::send_result, this, &MainWindow::receive_flag_edited_image);
	drawCircleForm->setFixedSize(530, 460);

	this->makeFrameForm = new MakeFrameForm(nullptr, &bmp_image);
	connect(makeFrameForm, &MakeFrameForm::send_result, this, &MainWindow::receive_flag_edited_image);
	makeFrameForm->setFixedSize(360, 300);

	//получаем величину рамки вокруг изображения для масштабирования
	int ind_border_image_start = ui->label->styleSheet().indexOf("border-width: ") + strlen("border-width: ");
	int ind_border_image_end = ui->label->styleSheet().indexOf("px;", ind_border_image_start);
	image_border_pxls = ui->label->styleSheet().midRef(ind_border_image_start,
	                                                   ind_border_image_end - ind_border_image_start).toInt();

	//создаём временный файл как буфер для отображения изображения
	char *str = new char[20];
	strcpy(str, "./.tempresXXXXXX");
	if (mkstemp(str) == -1) {
		std::clog << "Failed to find temporary filename\n";
		QMessageBox::critical(this, "Ошибка", "Не получилось сгенерировать имя временного файла!");
		exit(0);
	}
	else
		std::clog << "Temp filename: " << std::string(str) << '\n';
	name_temp_file = QString::fromStdString(str);
	delete[] str;

	//загрузка изображения
	if (bmp_image.input_image(name_file.toStdString())) {
		loaded_image = true;
		start_bmp_image = bmp_image;
		ui->height_label->setText(QString::number(bmp_image.get_height()));
		ui->width_label->setText(QString::number(bmp_image.get_width()));
		ui->bit_pixels_label->setText(QString::number(bmp_image.get_bit_pixels()));
		ui->size_byte_label->setText(QString::number(bmp_image.get_size()));
	}
	else {
		loaded_image = false;
		name_file = "";
		ui->label->setText("Здесь могло быть ваше изображение!");
		QMessageBox::critical(this, "Ошибка", "Не удалось загрузить изображение или формат не поддерживается!");
	}
}

MainWindow::~MainWindow() {
	delete image;
	delete squareForm;
	delete rgbFilterForm;
	delete rotateFragForm;
	delete drawCircleForm;
	delete makeFrameForm;
	std::clog << "MainWindow finished\n";
	remove(name_temp_file.toStdString().c_str());
	std::clog << "Temporary file removed\n";
	delete ui;
}

//SLOTs
void MainWindow::receive_flag_edited_image(bool was_edited) {
	image_edited = was_edited;
}
//end SLOTs

//сохранение во временный файл
void MainWindow::try_save() {
	if (image_edited) {
		if (!bmp_image.write_image(name_temp_file.toStdString())) {
			QMessageBox::critical(this, "Ошибка", "Не удалось сохранить промежутоный результат или файл!");
			return;
		}
		delete image;
		load_label_image(name_temp_file.toStdString());
	}
	image_edited = false;
	image_recover = false;
}

//загрузка изображения в виджет
void MainWindow::load_label_image(const std::string &name_file) {
	std::clog << "Image is starting load\n";
	image = new QPixmap(QString::fromStdString(name_file));
	*image = image->scaled(ui->label->width() - 2 * ui->label->margin() - 2 * image_border_pxls,
	                       ui->label->height() - 2 * ui->label->margin() - 2 * image_border_pxls,
	                       Qt::KeepAspectRatio/*Сохраняет пропорции*/);
	prev_label_w = ui->label->width();
	prev_label_h = ui->label->height();
	std::clog << "Label - H: " << ui->label->height() << ", W: " << ui->label->width() << "\n";
	std::clog << "Image - H: " << image->height() << ", W: " << image->width() << "\n";
	ui->label->setPixmap(*image);
	std::clog << "Image loaded\n";
}

//Возвращаем имя файла
std::string MainWindow::get_name_file() {
	return name_file.toStdString();
}

void MainWindow::on_draw_square_clicked() {
	if (loaded_image) {
		squareForm->init();
		squareForm->exec();
		try_save();
	}
	else {
		QMessageBox::critical(this, "Ошибка", "Изображение не было загружено!");
	}
}

void MainWindow::on_change_RGB_clicked() {
	if (loaded_image) {
		rgbFilterForm->init();
		rgbFilterForm->exec();
		try_save();
	}
	else {
		QMessageBox::critical(this, "Ошибка", "Изображение не было загружено!");
	}
}


void MainWindow::on_rotate_fragment_clicked() {
	if (loaded_image) {
		rotateFragForm->init();
		rotateFragForm->exec();
		try_save();
	}
	else {
		QMessageBox::critical(this, "Ошибка", "Изображение не было загружено!");
	}
}

void MainWindow::on_draw_circle_clicked() {
	if (loaded_image) {
		drawCircleForm->init();
		drawCircleForm->exec();
		try_save();
	}
	else {
		QMessageBox::critical(this, "Ошибка", "Изображение не было загружено!");
	}
}

void MainWindow::on_load_image_clicked() {
	name_file = QFileDialog::getOpenFileName(nullptr, "Открытие файла", "", "*.bmp");
	if (bmp_image.input_image(name_file.toStdString())) {
		loaded_image = true;
		start_bmp_image = bmp_image;
		ui->height_label->setText(QString::number(bmp_image.get_height()));
		ui->width_label->setText(QString::number(bmp_image.get_width()));
		ui->bit_pixels_label->setText(QString::number(bmp_image.get_bit_pixels()));
		ui->size_byte_label->setText(QString::number(bmp_image.get_size()));
		if(image != nullptr)
			delete image;
		load_label_image(name_file.toStdString());
	} else if(!name_file.isEmpty()) {
		QMessageBox::critical(this, "Ошибка", "Не удалось загрузить изображение или формат не поддерживается!");
	}
}

void MainWindow::on_save_image_clicked() {
	if (loaded_image) {
		name_file = QFileDialog::getSaveFileName(nullptr, "Сохранение файла", "", "*.bmp");
		if (!name_file.isEmpty() && !bmp_image.write_image(name_file.toStdString())) {
			QMessageBox::critical(this, "Ошибка", "Не удалось сохранить промежутоный результат или файл!");
			return;
		}
	}
	else {
		QMessageBox::critical(this, "Ошибка", "Изображение не было загружено!");
	}

}

void MainWindow::on_reload_image_clicked() {
	if (loaded_image && !image_recover) {
		bmp_image = start_bmp_image;
		if (!bmp_image.write_image(name_temp_file.toStdString())) {
			QMessageBox::critical(this, "Ошибка", "Не удалось сохранить промежутоный результат или файл!");
			return;
		}
		delete image;
		load_label_image(name_temp_file.toStdString());
		image_recover = true;
	}
	else if (!loaded_image) {
		QMessageBox::critical(this, "Ошибка", "Изображение не было загружено!");
	}

}

void MainWindow::on_reload_scale_clicked() {
	if (loaded_image && (ui->label->width() != prev_label_w || ui->label->height() != prev_label_h)) {
		if (!bmp_image.write_image(name_temp_file.toStdString())) {
			QMessageBox::critical(this, "Ошибка", "Не удалось сохранить промежутоный результат или файл!");
			return;
		}
		delete image;
		load_label_image(name_temp_file.toStdString());
		prev_label_w = ui->label->width();
		prev_label_h = ui->label->height();
	}
	else if(!loaded_image){
		QMessageBox::critical(this, "Ошибка", "Изображение не было загружено!");
	}
}

void MainWindow::on_info_clicked() {
	QMessageBox::information(this, "Информация",
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
	                         "Перезагрузить изображение: подогнать размер изображения под размер окна.\n\n"
	);
}



void MainWindow::on_make_frame_clicked()
{
	if (loaded_image) {
		makeFrameForm->init();
		makeFrameForm->exec();
		try_save();
	}
	else {
		QMessageBox::critical(this, "Ошибка", "Изображение не было загружено!");
	}
}
