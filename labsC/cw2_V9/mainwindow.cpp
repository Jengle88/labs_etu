#include <QLabel>
#include <iostream>
#include "libs/mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), ui(new Ui::MainWindow) {

	name_file = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.bmp");
	std::clog << "MainWindow created\n";
	ui->setupUi(this);

	this->squareForm = new CreateSquareForm(nullptr, &bmp_image);
	connect(squareForm, SIGNAL(send_results(bool)), this, SLOT(receiveEditedImage(bool)));
	squareForm->setFixedSize(460, 370);

	this->rgbFilterForm = new ChangeRGBFilterForm(nullptr, &bmp_image);
	connect(rgbFilterForm, SIGNAL(send_results(bool)), this, SLOT(receiveEditedImage(bool)));
	rgbFilterForm->setFixedSize(340, 210);

	this->rotateFragForm = new RotateFragmentForm(nullptr, &bmp_image);
	connect(rotateFragForm,SIGNAL(send_results(bool)), this, SLOT(receiveEditedImage(bool)));
	rotateFragForm->setFixedSize(450,250);

	this->drawCircleForm = new DrawCircleForm(nullptr, &bmp_image);
	connect(drawCircleForm,SIGNAL(send_results(bool)), this, SLOT(receiveEditedImage(bool)));
	drawCircleForm->setFixedSize(515,440);

	//Получаем величину рамки вокруг изображения
	int ind_border_image_start = ui->label->styleSheet().indexOf("border-width: ") + strlen("border-width: ");
	int ind_border_image_end = ui->label->styleSheet().indexOf("px;", ind_border_image_start);
	image_border_pxls = ui->label->styleSheet().midRef(ind_border_image_start, ind_border_image_end - ind_border_image_start).toInt();

	//Создаём временный файл как буфер для отображения изображения
	char* str1 = new char[20];
	strcpy(str1, "./.tempresXXXXXX");
	if(mkstemp(str1) == -1)
		std::clog << "Failed to find temporary filename\n";
	else
		std::clog << "Temp filename: " << std::string(str1) << '\n';
	name_temp_file = QString::fromStdString(str1);
	std::ofstream temp_file(name_temp_file.toStdString());
	if(temp_file.is_open())
		std::clog << "Temporary file created\n";
	else
		std::clog << "Temporary file not created\n";
	temp_file.close();
	delete[] str1;

	//загрузка изображения
	if(bmp_image.input_image(name_file.toStdString())){
		loaded_image = true;
		start_bmp_image = BMP(bmp_image);
		load_label_image(name_file.toStdString());
		ui->height_label->setText(QString::number(bmp_image.getHeight()));
		ui->width_label->setText(QString::number(bmp_image.getWidth()));
		ui->bit_pixels_label->setText(QString::number(bmp_image.getBitPerPixels()));
		ui->size_byte_label->setText(QString::number(bmp_image.getSize()));
	} else{
		loaded_image = false;
		ui->label->setText("Здесь могло быть ваше изображение!");
		QMessageBox::critical(this,"Attention!","Не удалось загрузить изображение!");
	}
}

MainWindow::~MainWindow() {
	delete image;
	delete squareForm;
	delete rgbFilterForm;
	delete rotateFragForm;
	delete drawCircleForm;
	std::clog << "MainWindow finished\n";
	remove(name_temp_file.toStdString().c_str());
	std::clog << "Temporary file removed\n";
	delete ui;
}
//SLOTs

void MainWindow::receiveEditedImage(bool was_edited) {
	this->image_edited = was_edited;
}
//end SLOTs
void MainWindow::try_save() {
	if(this->image_edited){
		bmp_image.write_image(name_temp_file.toStdString());
		delete image;
		load_label_image(name_temp_file.toStdString());
	}
	this->image_edited = false;
}

void MainWindow::load_label_image(const std::string name_file) {
	std::clog << "Image is starting load\n";
	image = new QPixmap(QString::fromStdString(name_file));
	*image = image->scaled(ui->label->width() - 2 * ui->label->margin() - 2 * image_border_pxls,
						ui->label->height() - 2 * ui->label->margin() - 2 * image_border_pxls, Qt::KeepAspectRatio/*Сохраняет пропорции*/);
	ui->label->setPixmap(*image);
	std::clog << "Image loaded\n";

}

void MainWindow::on_draw_square_clicked()
{
	if(loaded_image){
		squareForm->init();
		squareForm->exec();
		try_save();
	} else {
		QMessageBox::critical(nullptr,"Ошибка", "Изображение не было загружено!");
	}

}

void MainWindow::on_change_RGB_clicked()
{
	if(loaded_image){
		rgbFilterForm->init();
		rgbFilterForm->exec();
		try_save();
	} else {
		QMessageBox::critical(nullptr,"Ошибка", "Изображение не было загружено!");
	}
}


void MainWindow::on_rotate_fragment_clicked()
{
	if(loaded_image){
		rotateFragForm->init();
		rotateFragForm->exec();
		try_save();
	} else {
		QMessageBox::critical(nullptr,"Ошибка", "Изображение не было загружено!");
	}
}

void MainWindow::on_draw_circle_clicked()
{
	if(loaded_image){
		drawCircleForm->init();
		drawCircleForm->exec();
		try_save();
	} else {
		QMessageBox::critical(nullptr,"Ошибка", "Изображение не было загружено!");
	}
}

void MainWindow::on_load_image_clicked()
{
	name_file = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.bmp");
	if (!name_file.isEmpty() && bmp_image.input_image(name_file.toStdString())){
		loaded_image = true;
		start_bmp_image = bmp_image;
		ui->height_label->setText(QString::number(bmp_image.getHeight()));
		ui->width_label->setText(QString::number(bmp_image.getWidth()));
		ui->bit_pixels_label->setText(QString::number(bmp_image.getBitPerPixels()));
		ui->size_byte_label->setText(QString::number(bmp_image.getSize()));
		delete image;
		load_label_image(name_file.toStdString());
	} else{
		QMessageBox::critical(this,"Attention!","Не удалось загрузить изображение!");
	}
}

void MainWindow::on_save_image_clicked()
{
	if(loaded_image){
		name_file = QFileDialog::getSaveFileName(nullptr, "Save Dialog", "", "*.bmp");
		if (!name_file.isEmpty())
			bmp_image.write_image(name_file.toStdString());
	} else {
		QMessageBox::critical(nullptr,"Ошибка", "Изображение не было загружено!");
	}

}

void MainWindow::on_reload_image_clicked()
{
	if(loaded_image){
		bmp_image = start_bmp_image;
		bmp_image.write_image(name_temp_file.toStdString());
		delete image;
		load_label_image(name_temp_file.toStdString());
	} else {
		QMessageBox::critical(nullptr,"Ошибка", "Изображение не было загружено!");
	}

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
		"Перезагрузить изображение: подогнать размер изображения под размер окна.\n\n"
		   );
}

void MainWindow::on_reload_scale_clicked()
{
	if(loaded_image){
		bmp_image.write_image(name_temp_file.toStdString());
		delete image;
		load_label_image(name_temp_file.toStdString());
	} else {
		QMessageBox::critical(nullptr,"Ошибка", "Изображение не было загружено!");
	}
}
