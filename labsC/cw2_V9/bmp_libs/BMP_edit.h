#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <tuple>
#include <type_traits>

#define BMPFileHeaderSIZE 14

#define CLR_WHITE {255,255,255,0}
#define CLR_BLACK {0,0,0,0}
#define CLR_BLUE {255,0,0,0}
#define CLR_GREEN {0,255,0,0}
#define CLR_RED {0,0,255,0}
#define CLR_YELLOW {0,255,255,0}
#define CLR_PINK {127,0,255,0}
#define CLR_ORANGE {0,85,255,0}


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

//Фича: при повороте из-за добавления белых полей изображение может смещаться вправо

struct ColorItem {
	u_char Blue = 255;
	u_char Green = 255;
	u_char Red = 255;
	u_char Reserved = 0;

	ColorItem(u_char blue, u_char green, u_char red, u_char reserved);
	ColorItem();

	static bool is_correct_color(int blue, int green, int red, int reserved);
};

struct BMPFileHeader {
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
	//4 версия
	u_int RChannelBitmask = 0; //bV4RChannelBitmask битовые маски
	u_int GChannelBitmask = 0; //bV4GChannelBitmask битовые маски
	u_int BChannelBitmask = 0; //bV4BChannelBitmask битовые маски
	u_int AChannelBitmask = 0; //bV4AChannelBitmask битовые маски
	u_int ColorSpaceType = 0; //bV4ColorSpaceType вид цветового пространства
	u_int ColorSpaceEndpoints[9] = {0}; //bV4ColorSpaceEndpoints конечные точки
	u_int GammaRchannel = 0; //bV4GammaRchannel значение гаммы
	u_int GammaGchannel = 0; //bV4GammaGchannel значение гаммы
	u_int GammaBchannel = 0; //bV4GammaBchannel значение гаммы
	//5 версия
	u_int Intent = 0; //bV5Intent для рендеринга растра
	u_int ICCProfileData = 0; //bV5ICCProfileData смещение в байтах цветового профиля от BITMAPINFO
	u_int ICCProfileSize = 0; //bV5ICCProfileSize размер цветового профиля
	u_int Reserved = 0; //bV5Reserved зарезервированные нули
};


class BMP {
	BMPFileHeader file_header;
	BMPInfoHeader info_header;
	std::vector<ColorItem> colors;
	short cnt_extra_byte = 0; // выравнивание до кратности 4
	bool have_palette = false;

public:
	std::vector<std::vector<ColorItem>> pixels;
	BMP(BMPFileHeader bmp_file_header, BMPInfoHeader bmp_info_header,std::vector<ColorItem> palette,
	        std::vector<std::vector<ColorItem>> pixels);
	BMP() = default;

private:
	bool in_bmp_file_header(std::fstream &in);

	void in_bmp_info_header(std::fstream &in);

	void in_bmp_palette(std::fstream &in);

	void in_bmp_pixel_table(std::fstream &in);

	static void write_3_color(std::ofstream &out, ColorItem item);

	static void write_4_color(std::ofstream &out, ColorItem item);

	void draw_circle(int xcentr, int ycentr, int r, ColorItem color, bool have_center = true);

	std::vector<std::pair<int, int>> get_border_circle_in(int xcentr, int r, bool have_center = true) const;

	std::vector<std::pair<int, int>> get_border_circle_out(int xcentr, int r, bool have_center = true) const;

	void fill_circle(std::vector<std::pair<int, int>> &brd_ins, std::vector<std::pair<int, int>> &brd_out,
	                 int y, ColorItem line_color);


public:
	bool input_image(std::string name_file);

	void write_image(std::string name_file) const;

	int getWidth() const;

	int getHeight() const;

	void setWidth(int width);

	void setHeight(int height);

	int getSize() const;

	int getBitPerPixels() const;

	bool draw_square(int xpos, int ypos, int line_length, int line_width, ColorItem line_color,
	                 bool is_pour_over = false, ColorItem square_color = CLR_BLACK);

	bool edit_component(char component, int num);

	bool rotate_fragment(int xlpos, int ylpos, int xrpos, int yrpos, int angle);

	bool draw_circle_via_radius(int xpos, int ypos, int rad, int line_width, ColorItem line_color,
	                            bool is_pour_over = false, ColorItem circle_color = CLR_BLACK);

	bool
	draw_circle_via_square(int xposl, int yposl, int xposr, int yposr, int line_width, ColorItem line_color,
	                       bool is_pour_over = false, ColorItem circle_color = CLR_BLACK);
};
