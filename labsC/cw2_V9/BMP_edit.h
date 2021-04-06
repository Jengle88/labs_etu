#include "Byte.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <tuple>

#define BMPFileHeaderSIZE 14
#define BMPInfoHeaderSIZE 40
#define _4BYTE 4

/*
 * TODO:
 *  1) Сделать коммит
 *  2) Убрать поддержку не 24-битных изображений
 *  3) Перенести реализацию в cpp файл
 *  4) Сделать миграцию в проект Qt
 *  5) Coming soon...
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

void write_4_color(std::ofstream &out, const ColorItem &item) {
	out << item.rgbBlue << item.rgbGreen << item.rgbRed << item.rgbReserved;
}

void write_3_color(std::ofstream &out, const ColorItem &item) {
	out << item.rgbBlue << item.rgbGreen << item.rgbRed;
}

class BMP {

	BMPHeader file_header;
	BMPInfoHeader info_header;
	std::vector<ColorItem> colors;
	std::vector<std::vector<u_int16_t>> pixel_with_palette;
	std::vector<std::vector<ColorItem>> pixel_without_palette;
	short cnt_extra_byte = 0; // up to multiplicity 4
	bool have_palette = false;

	void in_bmp_file_header(std::fstream &in) {
		std::vector<u_char> byte;
		byte = Byte::get_byte(in, 2);
		this->file_header.Signature = Byte::make_short(byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->file_header.FileSize = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->file_header.Reserved = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->file_header.DataOffset = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
	}

	void in_bmp_info_header(std::fstream &in) {
		std::vector<u_char> byte;
		byte = Byte::get_byte(in, 4);
		this->info_header.Size = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->info_header.Width = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->info_header.Height = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 2);
		this->info_header.Planes = Byte::make_short(byte[1], byte[0]);
		byte = Byte::get_byte(in, 2);
		this->info_header.BitCount = Byte::make_short(byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->info_header.Compression = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->info_header.ImageSize = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->info_header.XpixelsPerM = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->info_header.YpixelsPerM = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->info_header.ColourUsed = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
		byte = Byte::get_byte(in, 4);
		this->info_header.ColorsImportant = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
	}

	void in_bmp_palette(std::fstream &in) {
		if(this->info_header.BitCount != 24){
			std::cout << "This image is not supported!";
			return;
		}
		switch (this->info_header.BitCount) {
			case 8:
				this->have_palette = true;
				this->colors.resize(256);
				for (int i = 0; i < 256; ++i) {
					this->colors[i] = {(u_char) in.get(), (u_char) in.get(),
									   (u_char) in.get(), (u_char) in.get()};
				}
				break;
			case 24:
				if (BMPFileHeaderSIZE + BMPInfoHeaderSIZE != this->file_header.DataOffset) {
					int palette_size =
							this->file_header.DataOffset - (BMPFileHeaderSIZE + BMPInfoHeaderSIZE);
					this->have_palette = true;
					this->colors.resize(palette_size);
					for (int i = 0; i < palette_size / 4; ++i) {
						this->colors[i] = {(u_char) in.get(), (u_char) in.get(),
										   (u_char) in.get(), (u_char) in.get()};
					}
				}
				break;
			default:
				std::cout << "This image is not supported!";
				break;

		}
	}

	void in_bmp_pixel_table(std::fstream &in) {
		switch (this->info_header.BitCount) {
			case 8:
				pixel_with_palette.resize(this->info_header.Height,
										  std::vector<u_int16_t>(this->info_header.Width));
				this->cnt_extra_byte = _4BYTE - int(3LL * this->info_header.Width % 4);
				for (int i = 0; i < this->info_header.Height; ++i) {
					for (int j = 0; j < this->info_header.Width; ++j) {
						this->pixel_with_palette[i][j] = in.get();
					}
					for (int j = 0; j < this->cnt_extra_byte; ++j) {
						in.get();
					}
				}
				break;
			case 24:
				pixel_without_palette.resize(this->info_header.Height,
											 std::vector<ColorItem>(this->info_header.Width));
				this->cnt_extra_byte = _4BYTE - int(3LL * this->info_header.Width % 4);
				for (int i = 0; i < this->info_header.Height; ++i) {
					for (int j = 0; j < this->info_header.Width; ++j) {
						this->pixel_without_palette[i][j] = {(u_char) in.get(), (u_char) in.get(),
															 (u_char) in.get(), (u_char) 0};
					}
					for (int j = 0; j < this->cnt_extra_byte; ++j) {
						in.get();
					}
				}
				break;
			case 32:
				pixel_without_palette.resize(this->info_header.Height,
											 std::vector<ColorItem>(this->info_header.Width));
				this->cnt_extra_byte = _4BYTE - int(3LL * this->info_header.Width % 4);
				for (int i = 0; i < this->info_header.Height; ++i) {
					for (int j = 0; j < this->info_header.Width; ++j) {
						this->pixel_without_palette[i][j] = {(u_char) in.get(), (u_char) in.get(),
															 (u_char) in.get(), (u_char) in.get()};
					}
					for (int j = 0; j < this->cnt_extra_byte; ++j) {
						in.get();
					}
				}
				break;
		}
	}

public:
	void input_picture(std::fstream &in) {
		in_bmp_file_header(in);
		in_bmp_info_header(in);
		in_bmp_palette(in);
		in_bmp_pixel_table(in);

	}

	void write_bmp(std::ofstream &out) const {
		Byte::write_16_like_byte(this->file_header.Signature, out);
		Byte::write_32_like_byte(this->file_header.FileSize, out);
		Byte::write_32_like_byte(this->file_header.Reserved, out);
		Byte::write_32_like_byte(this->file_header.DataOffset, out);

		Byte::write_32_like_byte(this->info_header.Size, out);
		Byte::write_32_like_byte(this->info_header.Width, out);
		Byte::write_32_like_byte(this->info_header.Height, out);
		Byte::write_16_like_byte(this->info_header.Planes, out);
		Byte::write_16_like_byte(this->info_header.BitCount, out);
		Byte::write_32_like_byte(this->info_header.Compression, out);
		Byte::write_32_like_byte(this->info_header.ImageSize, out);
		Byte::write_32_like_byte(this->info_header.XpixelsPerM, out);
		Byte::write_32_like_byte(this->info_header.YpixelsPerM, out);
		Byte::write_32_like_byte(this->info_header.ColourUsed, out);
		Byte::write_32_like_byte(this->info_header.ColorsImportant, out);

		if (this->have_palette) {
			for (int i = 0; i < this->colors.size(); ++i) {
				write_4_color(out, this->colors[i]);
			}
			for (int i = 0; i < this->info_header.Height; ++i) {
				for (int j = 0; j < this->info_header.Width; ++j) {
					out << this->pixel_with_palette[i][j];
				}
				for (int j = 0; j < this->cnt_extra_byte; ++j) {
					out << (u_char) 0;
				}
			}
		}
		else {
			if (this->info_header.BitCount == 24) {
				for (int i = 0; i < this->info_header.Height; ++i) {
					for (int j = 0; j < this->info_header.Width; ++j) {
						write_3_color(out, this->pixel_without_palette[i][j]);
					}
					for (int j = 0; j < this->cnt_extra_byte; ++j) {
						out << (u_char) 0;
					}
				}
			}
			else {

				for (int i = 0; i < this->info_header.Height; ++i) {
					for (int j = 0; j < this->info_header.Width; ++j) {
						write_4_color(out, this->pixel_without_palette[i][j]);
					}
					for (int j = 0; j < this->cnt_extra_byte; ++j) {
						out << (u_char) 0;
					}
				}
			}
		}
	}
};

