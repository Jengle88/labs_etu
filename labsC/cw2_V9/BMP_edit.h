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
#define CLR_YELLOW {0,255,255,0}


#define ERR_XYPOS "Bad x/y position for square!\n"
#define ERR_ANGLE "Bad angle!\n"
#define ERR_LRPOS "Bad right and left pos!\n"
#define ERR_RPOS "Bad right pos!\n"
#define ERR_LPOS "Bad left pos!\n"
#define ERR_HEIGHT "Bad height!\n"
#define ERR_WIDTH "Bad width!\n"
#define ERR_LENGTH "Bad line length!\n"
#define ERR_SQSHAPE "Shape is`n square!\n"
#define ERR_COMP "Bad component!\n"
#define ERR_CLR "Bad color!\n"
#define ERR_NFILE "Haven`t found file!\n"
#define ERR_IMAGE "This image is not supported!\n"
#define ERR_BMPIMAGE "This image is not BMP-file!\n"
#define ERR_RADIUS "Bad radius!\n"


/*
 * TODO:
 *  1) Сделать коммит --- V
 *  2) Убрать поддержку не 24-битных изображений --- V
 *  3) Перенести реализацию в cpp файл --- V
 *  4) Сделать миграцию в проект Qt --- V
 *  5) Убрать палитру --- V
 *  6) Сделать изменение размера изображения: выбор стороны и размера --- V
 *  7) Нарисовать квадрат и диагонали --- V
 *  8) Исправить рисование диагонали квадрата с правильной толщиной линии --- V
 *  9) Сделать поворот фрагмента на 180 --- V
 *  10) Сделать поворот фрагмента на 90 --- V
 *  11) Сделать поворот фрагмента на 270 --- V
 *  12) Нарисовать круг через радиус --- V
 *  13) Нарисовать круг через квадрат --- V
 *  14) Миграция в Qt
 *  15) Coming soon...
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
	u_char Blue = 255;
	u_char Green = 255;
	u_char Red = 255;
	u_char Reserved = 0;

	ColorItem(u_char blue, u_char green, u_char red, u_char reserved);
	ColorItem();
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
	void draw_circle(int xcentr, int ycentr, int r, ColorItem color, bool have_center = true);
	std::vector<std::pair<int,int>> get_border_circle_in(int xcentr, int r, bool have_center = true) const;
	std::vector<std::pair<int,int>> get_border_circle_out(int xcentr, int r, bool have_center = true) const;
	void fill_circle(std::vector<std::pair<int, int>> &brd_ins, std::vector<std::pair<int, int>> &brd_out,
				  int y, ColorItem line_color);


public:
	bool input_image(std::string &name_file);
	void write_bmp(std::string &name_file_output) const;
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);
	bool draw_square(int xpos, int ypos, int line_length, int line_width, ColorItem line_color,
					 bool is_pour_over = false, ColorItem square_color = CLR_BLACK);
	bool edit_component(char component, int num);
	bool rotate_fragment(int xlpos, int ylpos, int xrpos, int yrpos, int angle);
	bool draw_circle_via_radius(int xpos, int ypos, int rad, int line_width, ColorItem line_color,
								bool is_pour_over = false, ColorItem circle_color = CLR_BLACK);
	bool draw_circle_via_square(int xposl, int yposl, int xposr, int yposr, int line_width, ColorItem line_color,
							 bool is_pour_over = false, ColorItem circle_color = CLR_BLACK);
};

