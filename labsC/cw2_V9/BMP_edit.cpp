#include <cmath>
#include "BMP_edit.h"
#include "Byte.h"


void BMP::write_3_color(std::ofstream &out, const ColorItem &item) {
	out << item.rgbBlue << item.rgbGreen << item.rgbRed;
}

void BMP::write_4_color(std::ofstream &out, const ColorItem &item) {
	out << item.rgbBlue << item.rgbGreen << item.rgbRed << item.rgbReserved;
}

int BMP::in_bmp_file_header(std::fstream &in) {
	std::vector<u_char> byte;
	byte = Byte::get_byte(in, 2);
	this->file_header.Signature = Byte::make_short(byte[1], byte[0]);
	if(!Byte::compare_like_short(this->file_header.Signature, 'B', 'M')){//check!!!
		std::cout << "This image is not BMP-file!";                      //check!!!
		return 0;                                                        //check!!!
	}                                                                    //check!!!
	byte = Byte::get_byte(in, 4);
	this->file_header.FileSize = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
	byte = Byte::get_byte(in, 4);
	this->file_header.Reserved = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
	byte = Byte::get_byte(in, 4);
	this->file_header.DataOffset = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
	return 1;
}

void BMP::in_bmp_info_header(std::fstream &in) {
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

void BMP::in_bmp_palette(std::fstream &in) {
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
}

void BMP::in_bmp_pixel_table(std::fstream &in) {
	if (this->info_header.BitCount != 24)
		return;

	pixels.resize(this->info_header.Height,
				  std::vector<ColorItem>(this->info_header.Width));
	this->cnt_extra_byte = this->info_header.Width % 4;
	for (int i = this->info_header.Height - 1; i >= 0; i--) {
		for (int j = 0; j < this->info_header.Width; ++j) {
			this->pixels[i][j] = {(u_char) in.get(), (u_char) in.get(),
								  (u_char) in.get()};
		}
		for (int j = 0; j < this->cnt_extra_byte; ++j) {
			in.get();
		}
	}
}

bool BMP::input_picture(std::string &name_file) {
	std::fstream in(name_file, std::ios_base::binary | std::ios_base::in);
	if (!in.is_open()) {
		std::clog << "Haven`t found file!\n";
		return false;
	}
	if(!in_bmp_file_header(in))
		return false;
	in_bmp_info_header(in);
	if (this->info_header.BitCount == 24) {
		in_bmp_palette(in);
		in_bmp_pixel_table(in);
	}
	else {
		std::cout << "This image is not supported!";
	}
	in.close();
	return true;
}

void BMP::write_bmp(std::string &name_file_output) const {
	if (this->info_header.BitCount != 24) {
		return;
	}
	std::ofstream out(name_file_output, std::ios_base::binary | std::ios_base::out);

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
	}

	for (int i = this->info_header.Height - 1; i >= 0; i--) {
		for (int j = 0; j < this->info_header.Width; ++j) {
			write_3_color(out, this->pixels[i][j]);

		}
		for (int j = 0; j < this->cnt_extra_byte; ++j) {
			out << (u_char) 0;
		}
	}
	out.close();
}

void BMP::setWidth(int width) {
	if (width > 0 && width <= 6000) {
		for (int i = 0; i < this->info_header.Height; ++i) {
			this->pixels[i].resize(width);
		}
		if (this->info_header.Width < width) {
			for (int i = 0; i < this->info_header.Height; ++i) {
				for (int j = this->info_header.Width; j < width; ++j) {
					this->pixels[i][j] = CLR_WHITE;
				}
			}
		}
		this->info_header.Width = width;
	}
	else {
		/*Сообщение об ошибке*/
		std::cout << "Bad width!\n";
	}

}

void BMP::setHeight(int height) {
	if (height > 0 && height < 6000) {
		this->pixels.resize(height);
		if (this->info_header.Height < height) {
			for (int i = this->info_header.Height; i < height; ++i) {
				this->pixels[i] = std::vector<ColorItem>(this->info_header.Width, CLR_WHITE);
			}
		}
	}
	else {
		/*Сообщение об ошибке*/
		std::cout << "Bad height!\n";
	}
}

void // FIXME исправить толщину диагонали
BMP::draw_square(int xpos, int ypos, int line_length, int line_width, ColorItem line_color, bool is_pour_over,
				 ColorItem square_color) {
	if (xpos < 0 || xpos > this->info_header.Width || ypos < 0 || ypos > this->info_header.Height) {
		std::cout << "Bad x/y position for square!\n";
		return;
	}
	if (line_length < 0 || xpos + line_length >= this->info_header.Width ||
		ypos + line_length >= this->info_header.Height || line_length < 2 * line_width) {
		std::cout << "Bad line length!\n";
		return;
	}
	if (line_width < 0 || line_width > 50) {
		std::cout << "Bad line width!\n";
		return;
	}
	// первая верхняя линия
	for (int i = 0; i < line_width; ++i) {
		for (int j = 0; j < line_length; ++j) {
			this->pixels[ypos + i][xpos + j] = line_color;
		}
	}
	//боковые линии
	for (int i = line_width; i < line_length - line_width; ++i) {
		for (int j = 0; j < line_width; ++j) {
			this->pixels[ypos + i][xpos + j] = line_color;
		}
		for (int j = 0; j < line_width; ++j) {
			this->pixels[ypos + i][xpos + line_length - j - 1] = line_color;
		}
	}
	//нижняя линия
	for (int i = 0; i < line_width; ++i) {
		for (int j = 0; j < line_length; ++j) {
			this->pixels[ypos + line_length - i - 1][xpos + j] = line_color;
		}
	}
	//заливка
	if (is_pour_over) {
		for (int i = 0; i < line_length - 2 * line_width; ++i) {
			for (int j = 0; j < line_length - 2 * line_width; ++j) {
				this->pixels[ypos + line_width + i][xpos + line_width + j] = square_color;
			}
		}
	}
	//главная диагональ
	for (int i = 0; i < line_length - 2 * line_width; ++i) {
		this->pixels[ypos + line_width + i][xpos + line_width + i] = line_color;
	}
	//побочная диагональ
	for (int i = 0; i < line_length - 2 * line_width; ++i) {
		this->pixels[ypos + line_length - line_width - i - 1][xpos + line_width + i] = line_color;
	}
}

void BMP::edit_component(char component, int num) {
	if (component != 'r' && component != 'g' && component != 'b') {
		std::cout << "Bad component!\n";
		return;
	}
	if (num < 0 || num > 255) {
		std::cout << "Bad color!\n";
		return;
	}
	for (int i = 0; i < this->info_header.Height; ++i) {
		for (int j = 0; j < this->info_header.Width; ++j) {
			switch (component) {
				case 'r':
					this->pixels[i][j].rgbRed = num;
					break;
				case 'g':
					this->pixels[i][j].rgbGreen = num;
					break;
				case 'b':
					this->pixels[i][j].rgbBlue = num;
					break;
			}
		}
	}
}

void BMP::rotate_fragment(int xlpos, int ylpos, int xrpos, int yrpos, int angle) {
	if (xlpos < 0 || xlpos > this->info_header.Width || ylpos < 0 || ylpos > this->info_header.Height) {
		std::cout << "Bad left pos!\n";
		return;
	}
	if (xrpos < 0 || xrpos > this->info_header.Width || yrpos < 0 || yrpos > this->info_header.Height) {
		std::cout << "Bad right pos!\n";
		return;
	}
	if (xlpos > xrpos || ylpos > yrpos) {
		std::cout << "Bad right and left pos!\n";
		return;
	}

	if (angle == 90) {
		int ydelta = (yrpos - ylpos) / 2;
		int xdelta = (xrpos - xlpos) / 2;
		std::vector<std::vector<ColorItem>> temp_matrix(yrpos - ylpos + 1,
														std::vector<ColorItem>(xrpos - xlpos + 1));
		for (int i = ylpos; i <= yrpos; ++i) {
			for (int j = xlpos; j <= xrpos; ++j) {
				temp_matrix[i - ylpos][j - xlpos] = this->pixels[i][j];
				this->pixels[i][j] = CLR_WHITE;
			}
		}
		int new_x_start = std::max(0, xlpos + xdelta - ydelta);
		int new_y_start = std::max(0, ylpos + ydelta - xdelta);
		for (int i = 0; i < temp_matrix[0].size() && i + new_y_start < this->info_header.Height; ++i) {
			for (int j = 0; j < temp_matrix.size() && j + new_x_start < this->info_header.Width; ++j) {
				this->pixels[i + new_y_start][j + new_x_start] = temp_matrix[temp_matrix.size() - 1 - j][i];
			}
		}
	}
	else if (angle == 180) {
		int ydelta = (yrpos - ylpos) / 2;
		int xdelta = (xrpos - xlpos);
		for (int i = 0; i <= ydelta; ++i) {
			for (int j = 0; j <= xdelta; ++j) {
				std::swap(this->pixels[ylpos + i][xlpos + j], this->pixels[yrpos - i][xrpos - j]);
			}
		}
		if ((yrpos - ylpos + 1) % 2 != 0) {
			for (int i = 0; i < xdelta / 2; ++i) {
				std::swap(this->pixels[ylpos + ydelta][xlpos + i],
						  this->pixels[ylpos + ydelta][xrpos - i]);
			}
		}
	}
	else if (angle == 270) {
		int ydelta = (yrpos - ylpos) / 2;
		int xdelta = (xrpos - xlpos) / 2;
		std::vector<std::vector<ColorItem>> temp_matrix(yrpos - ylpos + 1,
														std::vector<ColorItem>(xrpos - xlpos + 1));
		for (int i = ylpos; i <= yrpos; ++i) {
			for (int j = xlpos; j <= xrpos; ++j) {
				temp_matrix[i - ylpos][j - xlpos] = this->pixels[i][j];
				this->pixels[i][j] = CLR_WHITE;
			}
		}
		int new_x_start = std::max(0, xlpos + xdelta - ydelta);
		int new_y_start = std::max(0, ylpos + ydelta - xdelta);
		for (int i = 0; i < temp_matrix[0].size() && i + new_y_start < this->info_header.Height; ++i) {
			for (int j = 0; j < temp_matrix.size() && j + new_x_start < this->info_header.Width; ++j) {
				this->pixels[i + new_y_start][j + new_x_start] = temp_matrix[j][temp_matrix[0].size() - 1 - i];
			}
		}
	}
	else
		std::cout << "Bad angle!\n";
}

int BMP::getWidth() const {
	return this->info_header.Width;
}

int BMP::getHeight() const {
	return this->info_header.Height;
}




