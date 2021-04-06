#include "Byte.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <tuple>

#define BMPFileHeaderSIZE 14
#define BMPInfoHeaderSIZE 40

/*
 * TODO:
 *  1) Сделать коммит --- V
 *  2) Убрать поддержку не 24-битных изображений --- V
 *  3) Перенести реализацию в cpp файл --- V
 *  4) Сделать миграцию в проект Qt
 *  5) Убрать палитру --- V
 *  6) Coming soon...
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
	u_char rgbBlue = 0;
	u_char rgbGreen = 0;
	u_char rgbRed = 0;
	u_char rgbReserved = 0;

};

void write_3_color(std::ofstream &out, const ColorItem &item);
void write_4_color(std::ofstream &out, const ColorItem &item);

class BMP {

	BMPHeader file_header;
	BMPInfoHeader info_header;
	std::vector<ColorItem> colors;
	short cnt_extra_byte = 0; // up to multiplicity 4
	bool have_palette = false;

public:
	std::vector<std::vector<ColorItem>> pixels;

private:
	void in_bmp_file_header(std::fstream &in);
	void in_bmp_info_header(std::fstream &in);
	void in_bmp_palette(std::fstream &in);
	void in_bmp_pixel_table(std::fstream &in);

public:
	void input_picture(std::string &name_file);
	void write_bmp(std::string &name_file_output) const;
};

