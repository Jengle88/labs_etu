#include "BMP_edit.h"
#include "Byte.h"


ColorItem::ColorItem(u_char blue, u_char green, u_char red, u_char reserved) {
	Blue = blue;
	Green = green;
	Red = red;
	Reserved = reserved;
}

bool ColorItem::is_correct_color(int blue, int green, int red, int reserved) {
	return 0 <= blue && blue <= 255 && 0 <= green && green <= 255 && 0 <= red && red <= 255 &&
	       0 <= reserved && reserved <= 255;
}

bool ColorItem::check(ColorItem item1, ColorItem item2) {
	return item1.Red == item2.Red && item1.Green == item2.Green && item1.Blue == item2.Blue &&
	       item1.Reserved == item2.Reserved;
}

ColorItem::ColorItem() = default;


void BMP::write_3_color(std::ofstream &out, ColorItem item) {
	out << item.Blue << item.Green << item.Red;
}

void BMP::write_4_color(std::ofstream &out, ColorItem item) {
	out << item.Blue << item.Green << item.Red << item.Reserved;
}

BMP::BMP(BMPFileHeader bmp_file_header, BMPInfoHeader bmp_info_header, std::vector<ColorItem> palette,
         std::vector<std::vector<ColorItem>> pixels) {
	this->file_header = bmp_file_header;
	this->info_header = bmp_info_header;
	if (!palette.empty()) {
		this->have_palette = true;
		this->colors = palette;
	}
	else {
		this->have_palette = false;
	}
	this->pixels = pixels;
	this->cnt_extra_byte = (4 - int(this->info_header.Width * 3) % 4) % 4;
}


bool BMP::in_bmp_file_header(std::fstream &in) {
	char byte[4];
	in.read(byte, 2);
	file_header.Signature = Byte::make_short(byte[0], byte[1]);
	in.read(byte, 4);
	file_header.FileSize = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	file_header.Reserved = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	file_header.DataOffset = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);

	if (!Byte::compare_like_short(file_header.Signature, 'B', 'M')) {
		std::cerr << ERR_BMPIMAGE;
		return false;
	}
	return true;
}

void BMP::in_bmp_info_header(std::fstream &in) {
	char byte[4];
	in.read(byte, 4);
	info_header.Size = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	info_header.Width = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	info_header.Height = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 2);
	info_header.Planes = Byte::make_short(byte[0], byte[1]);
	in.read(byte, 2);
	info_header.BitCount = Byte::make_short(byte[0], byte[1]);
	in.read(byte, 4);
	info_header.Compression = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	info_header.ImageSize = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	info_header.XpixelsPerM = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	info_header.YpixelsPerM = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	info_header.ColourUsed = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte, 4);
	info_header.ColorsImportant = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);

	if (info_header.Size >= 108) {
		in.read(byte, 4);
		info_header.RChannelBitmask = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.GChannelBitmask = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.BChannelBitmask = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.AChannelBitmask = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.ColorSpaceType = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		for (int i = 0; i < 9; ++i) {
			in.read(byte, 4);
			info_header.ColorSpaceEndpoints[i] = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		}
		in.read(byte, 4);
		info_header.GammaRchannel = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.GammaGchannel = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.GammaBchannel = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	}

	if (info_header.Size == 124) {
		in.read(byte, 4);
		info_header.Intent = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.ICCProfileData = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.ICCProfileSize = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		info_header.Reserved = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	}

}

void BMP::in_bmp_palette(std::fstream &in) {
	if (BMPFileHeaderSIZE + info_header.Size != file_header.DataOffset) {
		int palette_size =
				(int) file_header.DataOffset - (BMPFileHeaderSIZE + (int) info_header.Size);
		have_palette = true;
		colors.resize(palette_size);
		for (int i = 0; i < palette_size / 4; ++i) {
			u_char b = in.get();
			u_char g = in.get();
			u_char r = in.get();
			u_char res = in.get();
			colors[i] = ColorItem(b, g, r, res);
		}
	}
	else {
		have_palette = false;
		colors.clear();
	}
}

void BMP::in_bmp_pixel_table(std::fstream &in) {

	switch (info_header.BitCount) {
		case 24:
			pixels.resize(info_header.Height);
			for (int i = 0; i < pixels.size(); ++i) {
				pixels[i].resize(info_header.Width);
			}
			cnt_extra_byte = (4 - int(info_header.Width * 3) % 4) % 4;
			for (int i = (int) info_header.Height - 1; i >= 0; i--) {
				for (int j = 0; j < info_header.Width; ++j) {
					u_char b = in.get();
					u_char g = in.get();
					u_char r = in.get();
					pixels[i][j] = ColorItem(b, g, r, 0);
				}
				for (int j = 0; j < cnt_extra_byte; ++j) {
					in.get();
				}
			}
			break;
		default:
			return;
	}
}

bool BMP::input_image(const std::string name_file) {
	std::fstream in(name_file, std::ios_base::binary | std::ios_base::in);
	if (!in.is_open()) {
		std::cerr << ERR_NFILE;
		return false;
	}
	BMPFileHeader temp_file_header = file_header;
	BMPInfoHeader temp_info_header = info_header;
	if (!in_bmp_file_header(in)) {
		file_header = temp_file_header;
		return false;
	}
	in_bmp_info_header(in);
	switch (info_header.BitCount) {
		case 24:
			in_bmp_palette(in);
			in_bmp_pixel_table(in);
			break;
		default:
			file_header = temp_file_header;
			info_header = temp_info_header;
			std::cerr << ERR_IMAGE;
			in.close();
			return false;
	}

	in.close();
	return true;
}

bool BMP::write_image(std::string name_file) const {
	if (info_header.BitCount != 24) {
		std::clog << "Unsupported bit per pixels\n";
		return false;
	}

	std::ofstream out(name_file, std::ios_base::binary | std::ios_base::out);
	if (!out.is_open()) {
		std::clog << "Error write image\n";
		return false;
	}

	Byte::write_16_like_byte(file_header.Signature, out);
	Byte::write_32_like_byte(file_header.FileSize, out);
	Byte::write_32_like_byte(file_header.Reserved, out);
	Byte::write_32_like_byte(file_header.DataOffset, out);

	Byte::write_32_like_byte(info_header.Size, out);
	Byte::write_32_like_byte(info_header.Width, out);
	Byte::write_32_like_byte(info_header.Height, out);
	Byte::write_16_like_byte(info_header.Planes, out);
	Byte::write_16_like_byte(info_header.BitCount, out);
	Byte::write_32_like_byte(info_header.Compression, out);
	Byte::write_32_like_byte(info_header.ImageSize, out);
	Byte::write_32_like_byte(info_header.XpixelsPerM, out);
	Byte::write_32_like_byte(info_header.YpixelsPerM, out);
	Byte::write_32_like_byte(info_header.ColourUsed, out);
	Byte::write_32_like_byte(info_header.ColorsImportant, out);

	if (info_header.Size >= 108) {
		Byte::write_32_like_byte(info_header.RChannelBitmask, out);
		Byte::write_32_like_byte(info_header.GChannelBitmask, out);
		Byte::write_32_like_byte(info_header.BChannelBitmask, out);
		Byte::write_32_like_byte(info_header.AChannelBitmask, out);
		Byte::write_32_like_byte(info_header.ColorSpaceType, out);
		for (int i = 0; i < 9; ++i)
			Byte::write_32_like_byte(info_header.ColorSpaceEndpoints[i], out);
		Byte::write_32_like_byte(info_header.GammaRchannel, out);
		Byte::write_32_like_byte(info_header.GammaGchannel, out);
		Byte::write_32_like_byte(info_header.GammaBchannel, out);
	}

	if (info_header.Size >= 124) {
		Byte::write_32_like_byte(info_header.Intent, out);
		Byte::write_32_like_byte(info_header.ICCProfileData, out);
		Byte::write_32_like_byte(info_header.ICCProfileSize, out);
		Byte::write_32_like_byte(info_header.Reserved, out);
	}

	if (have_palette) {
		for (int i = 0; i < colors.size(); ++i) {
			write_4_color(out, colors[i]);
		}
	}

	for (int i = (int) info_header.Height - 1; i >= 0; i--) {
		for (int j = 0; j < info_header.Width; ++j) {
			write_3_color(out, pixels[i][j]);
		}
		for (int j = 0; j < cnt_extra_byte; ++j) {
			out << (u_char) 0;
		}
	}
	out.close();
	return true;
}

int BMP::get_width() const {
	return info_header.Width;
}

int BMP::get_height() const {
	return info_header.Height;
}

void BMP::set_width(int width) {
	if (width > 0 && width <= 6000) {
		for (int i = 0; i < info_header.Height; ++i) {
			pixels[i].resize(width);
		}
		if (info_header.Width < width) {
			for (int i = 0; i < info_header.Height; ++i) {
				for (int j = (int) info_header.Width; j < width; ++j) {
					pixels[i][j] = CLR_WHITE;
				}
			}
		}
		info_header.Width = width;
		cnt_extra_byte = (4 - int(info_header.Width * 3) % 4) % 4;
		file_header.FileSize = file_header.DataOffset + info_header.Height *
		                                                (3 * info_header.Width + cnt_extra_byte);
	}
	else {
		std::cerr << ERR_WIDTH;
	}

}

void BMP::set_height(int height) {
	if (height > 0 && height <= 6000) {
		pixels.resize(height);
		if (info_header.Height < height) {
			for (int i = (int) info_header.Height; i < height; ++i) {
				pixels[i] = std::vector<ColorItem>(info_header.Width, CLR_WHITE);
			}
		}
		info_header.Height = height;
		file_header.FileSize = file_header.DataOffset + info_header.Height *
		                                                (3 * info_header.Width + cnt_extra_byte);
	}
	else {
		std::cerr << ERR_HEIGHT;
	}
}

int BMP::get_size() const {
	return file_header.FileSize;
}

int BMP::get_bit_pixels() const {
	return info_header.BitCount;
}


bool
BMP::draw_square(int xpos, int ypos, int line_length, int line_width, ColorItem line_color, bool is_pour_over,
                 ColorItem square_color) {
	if (xpos < 0 || xpos >= info_header.Width || ypos < 0 || ypos >= info_header.Height) {
		std::cerr << ERR_XYPOS;
		return false;
	}
	if (line_length <= 0 || xpos + line_length > info_header.Width ||
	    ypos + line_length > info_header.Height || line_length < 2 * line_width) {
		std::cerr << ERR_LENGTH;
		return false;
	}
	if (line_width <= 0) {
		std::cerr << ERR_WIDTH;
		return false;
	}
	// верхняя и нижняя линии
	for (int i = 0; i < line_width; ++i) {
		for (int j = 0; j < line_length; ++j) {
			pixels[ypos + i][xpos + j] = line_color;
			pixels[ypos + line_length - i - 1][xpos + j] = line_color;

		}
	}
	//боковые линии
	for (int i = line_width; i < line_length - line_width; ++i) {
		for (int j = 0; j < line_width; ++j) {
			pixels[ypos + i][xpos + j] = line_color;
			pixels[ypos + i][xpos + line_length - j - 1] = line_color;

		}
	}
	//заливка
	if (is_pour_over) {
		for (int i = 0; i < line_length - 2 * line_width; ++i) {
			for (int j = 0; j < line_length - 2 * line_width; ++j) {
				pixels[ypos + line_width + i][xpos + line_width + j] = square_color;
			}
		}
	}
	//главная диагональ
	//строим сверху вниз и вправо
	for (int i = 0; i < line_length - 2 * line_width; ++i) {
		pixels[ypos + line_width + i][xpos + line_width + i] = line_color;//главная линия
		for (int j = 1; j <= line_width - 1; ++j) {
			pixels[ypos + line_width + i + j][xpos + line_width + i] = line_color;//расширение
			pixels[ypos + line_width + i][xpos + line_width + i + j] = line_color;
		}
	}
	//побочная диагональ
	//строим сверху вниз и влево
	for (int i = 0; i < line_length - 2 * line_width; ++i) {
		pixels[ypos + line_length - line_width - i - 1][xpos + line_width + i] = line_color;//главная линия
		for (int j = 1; j <= line_width - 1; ++j) {
			pixels[ypos + line_length - line_width - i - 1 + j][xpos + line_width + i] = line_color;
			pixels[ypos + line_length - line_width - i - 1][xpos + line_width + i -
			                                                j] = line_color;//расширение
		}
	}
	return true;
}

bool BMP::edit_component(char component, int num) {
	if (component != 'r' && component != 'g' && component != 'b') {
		std::cerr << ERR_COMP;
		return false;
	}
	if (num < 0 || num > 255) {
		std::cerr << ERR_CLR;
		return false;
	}
	switch (component) {
		case 'r':
			for (int i = 0; i < info_header.Height; ++i) {
				for (int j = 0; j < info_header.Width; ++j) {
					pixels[i][j].Red = num;
				}
			}
			break;
		case 'g':
			for (int i = 0; i < info_header.Height; ++i) {
				for (int j = 0; j < info_header.Width; ++j) {
					pixels[i][j].Green = num;
				}
			}
			break;
		case 'b':
			for (int i = 0; i < info_header.Height; ++i) {
				for (int j = 0; j < info_header.Width; ++j) {
					pixels[i][j].Blue = num;
				}
			}
			break;
	}
	return true;
}

bool BMP::rotate_fragment(int xlpos, int ylpos, int xrpos, int yrpos, int angle) {
	if (xlpos < 0 || xlpos >= info_header.Width || ylpos < 0 || ylpos >= info_header.Height) {
		std::cerr << ERR_LPOS;
		return false;
	}
	if (xrpos < 0 || xrpos >= info_header.Width || yrpos < 0 || yrpos >= info_header.Height) {
		std::cerr << ERR_RPOS;
		return false;
	}
	if (xlpos > xrpos || ylpos > yrpos) {
		std::cerr << ERR_LRPOS;
		return false;
	}

	if (angle == 90) {
		int ydelta = (yrpos - ylpos) / 2;//смещение для центра
		int xdelta = (xrpos - xlpos) / 2;
		std::vector<std::vector<ColorItem>> temp_matrix(yrpos - ylpos + 1,//временная матрица для элементов
		                                                std::vector<ColorItem>(xrpos - xlpos + 1));
		for (int i = ylpos; i <= yrpos; ++i) {
			for (int j = xlpos; j <= xrpos; ++j) {
				temp_matrix[i - ylpos][j - xlpos] = pixels[i][j];
				pixels[i][j] = CLR_WHITE;
			}
		}
		int new_x_start = std::max(0, xlpos + xdelta - ydelta);//новые значения XY для прямоугольника
		int new_y_start = std::max(0, ylpos + ydelta - xdelta);
		for (int i = 0; i < temp_matrix[0].size() && i + new_y_start < info_header.Height; ++i) {
			for (int j = 0; j < temp_matrix.size() && j + new_x_start < info_header.Width; ++j) {
				pixels[i + new_y_start][j + new_x_start] = temp_matrix[temp_matrix.size() - 1 - j][i];
			}
		}
	}
	else if (angle == 180) {
		int ydelta = (yrpos - ylpos) / 2;
		int xdelta = (xrpos - xlpos);
		for (int i = 0; i <= ydelta; ++i) {//смещаем по линиям
			for (int j = 0; j <= xdelta; ++j) {
				std::swap(pixels[ylpos + i][xlpos + j],
				          pixels[yrpos - i][xrpos - j]);
			}
		}
		if ((yrpos - ylpos + 1) % 2 != 0) {//если осталась одна линия
			for (int i = 0; i < xdelta / 2; ++i) {
				std::swap(pixels[ylpos + ydelta][xlpos + i],
				          pixels[ylpos + ydelta][xrpos - i]);
			}
		}
	}
	else if (angle == 270) {
		int ydelta = (yrpos - ylpos) / 2;//смещение для центра
		int xdelta = (xrpos - xlpos) / 2;
		std::vector<std::vector<ColorItem>> temp_matrix(yrpos - ylpos + 1,//временная матрица для элементов
		                                                std::vector<ColorItem>(xrpos - xlpos + 1));
		for (int i = ylpos; i <= yrpos; ++i) {
			for (int j = xlpos; j <= xrpos; ++j) {
				temp_matrix[i - ylpos][j - xlpos] = pixels[i][j];
				pixels[i][j] = CLR_WHITE;
			}
		}
		int new_x_start = std::max(0, xlpos + xdelta - ydelta);//новые значения XY для прямоугольника
		int new_y_start = std::max(0, ylpos + ydelta - xdelta);
		for (int i = 0; i < temp_matrix[0].size() && i + new_y_start < info_header.Height; ++i) {
			for (int j = 0; j < temp_matrix.size() && j + new_x_start < info_header.Width; ++j) {
				pixels[i + new_y_start][j + new_x_start] = temp_matrix[j][temp_matrix[0].size() - 1 - i];
			}
		}
	}
	else {
		std::cerr << ERR_ANGLE;
		return false;
	}
	return true;
}


bool
BMP::draw_circle_radius(int xpos, int ypos, int rad, int line_width, ColorItem line_color,
                        bool is_pour_over, ColorItem circle_color) {
	if (xpos < 0 || xpos >= info_header.Width || ypos < 0 || ypos >= info_header.Height ||
	    xpos - rad - line_width + 1 < 0 || xpos + rad + line_width > info_header.Width ||
	    ypos - rad - line_width + 1 < 0 || ypos + rad + line_width > info_header.Height) {
		std::cerr << ERR_XYPOS;
		return false;
	}
	if (rad <= 0) {
		std::cerr << ERR_RADIUS;
		return false;
	}
	if (line_width <= 0) {
		std::cerr << ERR_WIDTH;
		return false;
	}
	draw_circle(xpos, ypos, rad, line_color);//меньшая окружность(от точки до линии длина rad - 1)
	draw_circle(xpos, ypos, rad + line_width - 1, line_color);//большая окружность
	auto borders_greater_circle_out = get_border_circle_out(xpos, rad + line_width - 1, true);
	auto borders_less_circle_out = get_border_circle_out(xpos, rad, true);
	auto borders_less_circle_in = get_border_circle_in(xpos, rad, true);
	//заполняем пространство между окружностями
	fill_circle(borders_less_circle_out, borders_greater_circle_out, ypos - rad - line_width + 1, line_color);
	if (is_pour_over) {
		for (int i = 1; i <= 2 * rad; ++i) {
			for (int j = borders_less_circle_in[i].first + 1; j < borders_less_circle_in[i].second; ++j) {
				pixels[ypos - rad + i][j] = circle_color;
			}
		}
	}
	return true;
}

bool
BMP::draw_circle_square(int xposl, int yposl, int xposr, int yposr, int line_width, ColorItem line_color,
                        bool is_pour_over, ColorItem circle_color) {
	if (xposl >= xposr || yposl >= yposr || xposl < 0 || xposl >= info_header.Width ||
	    xposr < 0 || xposr >= info_header.Width || yposl < 0 || yposl >= info_header.Height ||
	    yposr < 0 || yposr >= info_header.Height) {
		std::clog << ERR_XYPOS;
		return false;
	}
	if (xposr - xposl != yposr - yposl) {
		std::clog << ERR_SQSHAPE;
		return false;
	}
	int xcentr = (xposr + xposl) / 2;//центр окружности
	int ycentr = (yposr + yposl) / 2;
	int radius = xcentr - xposl - line_width + 1;
	if (radius < 0) {
		std::clog << ERR_WIDTH;
		return false;
	}
	if ((xposr - xposl) % 2 == 0)//если есть действительный центр
		draw_circle_radius(xcentr, ycentr, radius, line_width, line_color, is_pour_over, circle_color);
	else {//если центр мнимый(нет такого пикселя)
		draw_circle(xcentr, ycentr, radius, line_color, false);
		draw_circle(xcentr, ycentr, radius + line_width - 1, line_color, false);
		auto borders_greater_circle_out = get_border_circle_out(xcentr, radius + line_width - 1, false);
		auto borders_less_circle_out = get_border_circle_out(xcentr, radius, false);
		auto borders_less_circle_in = get_border_circle_in(xcentr, radius, false);
		fill_circle(borders_less_circle_out, borders_greater_circle_out, ycentr - radius - line_width + 1,
		            line_color);
		if (is_pour_over) {
			for (int i = 1; i <= 2 * radius; ++i) {
				for (int j = borders_less_circle_in[i].first + 1; j < borders_less_circle_in[i].second; ++j) {
					pixels[ycentr - radius + i][j] = circle_color;
				}
			}
		}
	}
	return true;
}

void
BMP::fill_circle(std::vector<std::pair<int, int>> &brd_ins, std::vector<std::pair<int, int>> &brd_out, int y,
                 ColorItem line_color) {
	int delta_size = ((int) brd_out.size() - (int) brd_ins.size()) / 2;
	y++;//тк самый верхний пиксель изменять не нужно
	for (int i = 1; i < delta_size; ++i) {//верхняя часть
		for (int j = brd_out[i].first + 1; j < brd_out[i].second; ++j) {
			pixels[y][j] = line_color;
		}
		y++;
	}
	int ind = 0;
	for (int i = delta_size; i < brd_out.size() - delta_size; ++i) {//между окружностями
		for (int j = brd_out[i].first + 1; j < brd_ins[ind].first; ++j) {
			pixels[y][j] = line_color;//левая часть
		}
		for (int j = brd_ins[ind].second + 1; j < brd_out[i].second; ++j) {
			pixels[y][j] = line_color;//правая часть
		}
		ind++;
		y++;
	}
	for (int i = (int) brd_out.size() - delta_size; i < brd_out.size() - 1; ++i) {//нижняя часть
		for (int j = brd_out[i].first + 1; j < brd_out[i].second; ++j) {
			pixels[y][j] = line_color;
		}
		y++;
	}
}

void BMP::draw_circle(int xcentr, int ycentr, int r, ColorItem color, bool have_center) {
	have_center = !have_center;
	int dx = r;
	int dy = 0;
	int radiusError = 1 - dx;
	while (dx >= dy) {
		pixels[ycentr + have_center + dy][xcentr + have_center + dx] = color;
		pixels[ycentr + have_center + dx][xcentr + have_center + dy] = color;
		pixels[ycentr - dy][xcentr + have_center + dx] = color;
		pixels[ycentr - dx][xcentr + have_center + dy] = color;
		pixels[ycentr + have_center + dy][xcentr - dx] = color;
		pixels[ycentr + have_center + dx][xcentr - dy] = color;
		pixels[ycentr - dy][xcentr - dx] = color;
		pixels[ycentr - dx][xcentr - dy] = color;
		dy++;
		if (radiusError < 0) {//используется знак ошибки
			radiusError += 2 * dy + 1;//выводится из формулы, точка внутри окружности
		}
		else {
			dx--;
			radiusError += 2 * (dy - dx + 1);//выводится из формулы, точка была бы вне окружности
		}
	}
}

std::vector<std::pair<int, int>> BMP::get_border_circle_in(int xcentr, int r, bool have_center) const {
	have_center = !have_center;
	int x = r;//симуляция алгоритма Брезенхема
	int y = 0;
	int radiusError = 1 - x;
	std::vector<std::pair<int, int>> borders(2 * r + 1 + have_center, {-1e9, 1e9});
	while (x >= y) {//берём нужные границы
		borders[r + have_center + y].second = std::min(borders[r + have_center + y].second,
		                                               xcentr + have_center + x);
		borders[r + have_center + x].second = std::min(borders[r + have_center + x].second,
		                                               xcentr + have_center + y);
		borders[r - y].second = std::min(borders[r - y].second, xcentr + have_center + x);
		borders[r - x].second = std::min(borders[r - x].second, xcentr + have_center + y);
		borders[r + have_center + y].first = std::max(borders[r + have_center + y].first, xcentr - x);
		borders[r + have_center + x].first = std::max(borders[r + have_center + x].first, xcentr - y);
		borders[r - y].first = std::max(borders[r - y].first, xcentr - x);
		borders[r - x].first = std::max(borders[r - x].first, xcentr - y);
		y++;
		if (radiusError < 0) {
			radiusError += 2 * y + 1;
		}
		else {
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
	return borders;
}

std::vector<std::pair<int, int>> BMP::get_border_circle_out(int xcentr, int r, bool have_center) const {
	have_center = !have_center;
	int x = r;
	int y = 0;
	int radiusError = 1 - x;
	std::vector<std::pair<int, int>> borders(2 * r + 1 + have_center, {1e9, -1e9});
	while (x >= y) {
		borders[r + have_center + y].second = std::max(borders[r + have_center + y].second,
		                                               xcentr + have_center + x);
		borders[r + have_center + x].second = std::max(borders[r + have_center + x].second,
		                                               xcentr + have_center + y);
		borders[r - y].second = std::max(borders[r - y].second, xcentr + have_center + x);
		borders[r - x].second = std::max(borders[r - x].second, xcentr + have_center + y);
		borders[r + have_center + y].first = std::min(borders[r + have_center + y].first, xcentr - x);
		borders[r + have_center + x].first = std::min(borders[r + have_center + x].first, xcentr - y);
		borders[r - y].first = std::min(borders[r - y].first, xcentr - x);
		borders[r - x].first = std::min(borders[r - x].first, xcentr - y);
		y++;
		if (radiusError < 0) {
			radiusError += 2 * y + 1;
		}
		else {
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
	return borders;
}

bool BMP::make_frame(int line_width, ColorItem line_color) {
	struct Point {
		int y, x;
		std::string dir = "";
	};
	if (line_width < 0 || line_width > info_header.Width || line_width > info_header.Height) {
		std::clog << "Bad width\n";
		return false;
	}
	std::vector<Point> border;
	for (int i = 0; i < info_header.Height; ++i) {
		for (int j = 0; j < info_header.Width; ++j) {
			if (ColorItem::check(pixels[i][j], CLR_WHITE)) {
				bool up = (i > 0 && !ColorItem::check(pixels[i - 1][j], CLR_WHITE));
				bool down = (i < info_header.Height - 1 && !ColorItem::check(pixels[i + 1][j], CLR_WHITE));
				bool left = (j > 0 && !ColorItem::check(pixels[i][j - 1], CLR_WHITE));
				bool right = (j < info_header.Width - 1 && !ColorItem::check(pixels[i][j + 1], CLR_WHITE));
				if (up) {
					if (right && !ColorItem::check(pixels[i - 1][j + 1], CLR_WHITE)) {
						border.push_back({i, j, "ur"});
					}
					if (left && !ColorItem::check(pixels[i - 1][j - 1], CLR_WHITE)) {
						border.push_back({i, j, "ul"});
					}
				}
				if (down) {
					if (right && !ColorItem::check(pixels[i + 1][j + 1], CLR_WHITE)) {
						border.push_back({i, j, "dr"});
					}
					if (left && !ColorItem::check(pixels[i + 1][j - 1], CLR_WHITE)) {
						border.push_back({i, j, "dl"});
					}
				}
				if (right)
					border.push_back({i, j, "r"});
				if (left)
					border.push_back({i, j, "l"});
				if (down)
					border.push_back({i, j, "d"});
				if (up)
					border.push_back({i, j, "u"});
			}
		}
	}
	for (int i = 0; i < border.size(); ++i) {
		if (border[i].dir == "ur") {
			for (int j = 1; j <= line_width && border[i].y - j >= 0; ++j) {
				for (int k = 1; k <= line_width && border[i].x + k < info_header.Width; ++k) {
					if (!ColorItem::check(pixels[border[i].y - j][border[i].x + k], CLR_WHITE))
						pixels[border[i].y - j][border[i].x + k] = line_color;
				}
			}
		}
		if (border[i].dir == "ul") {
			for (int j = 1; j <= line_width && border[i].y - j >= 0; ++j) {
				for (int k = 1; k <= line_width && border[i].x - k >= 0; ++k) {
					if (!ColorItem::check(pixels[border[i].y - j][border[i].x - k], CLR_WHITE))
						pixels[border[i].y - j][border[i].x - k] = line_color;
				}
			}
		}
		if (border[i].dir == "dr") {
			for (int j = 1; j <= line_width && border[i].y + j < info_header.Height; ++j) {
				for (int k = 1; k <= line_width && border[i].x + k < info_header.Width; ++k) {
					if (!ColorItem::check(pixels[border[i].y + j][border[i].x + k], CLR_WHITE))
						pixels[border[i].y + j][border[i].x + k] = line_color;
				}
			}
		}
		if (border[i].dir == "dl") {
			for (int j = 1; j <= line_width && border[i].y + j < info_header.Height; ++j) {
				for (int k = 1; k <= line_width && border[i].x - k >= 0; ++k) {
					if (!ColorItem::check(pixels[border[i].y + j][border[i].x - k], CLR_WHITE))
						pixels[border[i].y + j][border[i].x - k] = line_color;
				}
			}
		}
		if (border[i].dir == "u") {
			for (int j = 1; j <= line_width && border[i].y - j >= 0; ++j) {
				if (!ColorItem::check(pixels[border[i].y - j][border[i].x], CLR_WHITE))
					pixels[border[i].y - j][border[i].x] = line_color;
			}
		}
		if (border[i].dir == "d") {
			for (int j = 1; j <= line_width && border[i].y + j < info_header.Height; ++j) {
				if (!ColorItem::check(pixels[border[i].y + j][border[i].x], CLR_WHITE))
					pixels[border[i].y + j][border[i].x] = line_color;
			}
		}
		if (border[i].dir == "l") {
			for (int k = 1; k <= line_width && border[i].x - k >= 0; ++k) {
				if (!ColorItem::check(pixels[border[i].y][border[i].x - k], CLR_WHITE))
					pixels[border[i].y][border[i].x - k] = line_color;
			}
		}
		if (border[i].dir == "r") {
			for (int k = 1; k <= line_width && border[i].x + k < info_header.Width; ++k) {
				if (!ColorItem::check(pixels[border[i].y][border[i].x + k], CLR_WHITE))
					pixels[border[i].y][border[i].x + k] = line_color;
			}
		}
	}
	return true;
}

