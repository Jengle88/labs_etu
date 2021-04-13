#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <tuple>
#include <type_traits>

#define BMPFileHeaderSIZE 14
#define BMPInfoHeaderSIZE 40
#define CLR_WHITE {255,255,255,0}
#define CLR_BLACK {0,0,0,0}
#define CLR_BLUE {255,0,0,0}
#define CLR_GREEN {0,255,0,0}
#define CLR_RED {0,0,255,0}


/*
 * TODO:
 *  1) Сделать коммит --- V
 *  2) Убрать поддержку не 24-битных изображений --- V
 *  3) Перенести реализацию в cpp файл --- V
 *  4) Сделать миграцию в проект Qt --- V
 *  5) Убрать палитру --- V
 *  6) Сделать изменение размера изображения: выбор стороны и размера --- V
 *  7) Нарисовать квадрат и диагонали --- V
 *  8) Исправить рисование диагонали квадрата с правильной толщиной линии
 *  9) Сделать поворот фрагмента на 180 --- V
 *  10) Сделать поворот фрагмента на 90 --- V
 *  11) Сделать поворот фрагмента на 270 --- V
 *  12) Coming soon...
 */



struct BMPHeader {
	u_int16_t Signature = 0; //bfType тип файла. Должен быть 'B''M' для bmp
	u_int FileSize = 0; //bfSize размер файла в байтах
	u_int Reserved = 0; //bfReserved12 должны быть нули
	u_int DataOffset = 0; // bfOffBits где начало массива данных относительно начала файла

};

struct BMPInfoHeader {
	u_int Size = 0; //biSize размер структуры sizeof(BITMAPINFOHEADER)
	u_int Width = 0; //biWidth ширина картинки в пикселях
	u_int Height = 0; //biHeight высота картинки в пикселях
	u_int16_t Planes = 0; //biPlanes кол-во плоскостей(1)
	u_int16_t BitCount = 0; //biBitCount кол-во бит на пиксель
	u_int Compression = 0; //biCompression тип сжатия
	u_int ImageSize = 0; //biSizeImage (0)
	u_int XpixelsPerM = 0; //biXPelsPerMeter горизонтальное разрешение
	u_int YpixelsPerM = 0; //biYPelsPerMeter вертикальное разрешение
	u_int ColourUsed = 0; //biClrUsed кол-во цветов из таблицы (0 - макс число)
	u_int ColorsImportant = 0; //biClrImportant кол-во цветов, нужных для изображения (0 - все)

};

struct ColorItem {
	u_char rgbBlue = 255;
	u_char rgbGreen = 255;
	u_char rgbRed = 255;
	u_char rgbReserved = 0;

};



class BMP {

	BMPHeader file_header;
	BMPInfoHeader info_header;
	std::vector<ColorItem> colors;
	short cnt_extra_byte = 0; // up to multiplicity 4
	bool have_palette = false;

public:
	std::vector<std::vector<ColorItem>> pixels;

private:
	int in_bmp_file_header(std::fstream &in);
	void in_bmp_info_header(std::fstream &in);
	void in_bmp_palette(std::fstream &in);
	void in_bmp_pixel_table(std::fstream &in);
	static void write_3_color(std::ofstream &out, const ColorItem &item);
	static void write_4_color(std::ofstream &out, const ColorItem &item);

public:
	bool input_picture(std::string &name_file);
	void write_bmp(std::string &name_file_output) const;
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);

	void draw_square(int xpos, int ypos, int line_length, int line_width, ColorItem line_color,
				  bool is_pour_over = false, ColorItem square_color = CLR_WHITE);
	void edit_component(char component, int num);
	void rotate_fragment(int xlpos, int ylpos, int xrpos, int yrpos, int angle);
};

