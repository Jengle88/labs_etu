#include "BMP_edit.h"
#include "Byte.h"


void BMP::write_3_color(std::ofstream &out, const ColorItem &item) {
	out << item.Blue << item.Green << item.Red;
}

void BMP::write_4_color(std::ofstream &out, const ColorItem &item) {
	out << item.Blue << item.Green << item.Red << item.Reserved;
}

ColorItem::ColorItem(u_char blue, u_char green, u_char red, u_char reserved) {
	this->Blue = blue;
	this->Green = green;
	this->Red = red;
	this->Reserved = reserved;
}

bool ColorItem::is_correct_color(int b, int g, int r, int reserv) {
	return 0 <= b && b <= 255 && 0 <= g && g <= 255 && 0 <= r && r <= 255 && 0 <= reserv && reserv <= 255;
}

ColorItem::ColorItem() = default;

int BMP::in_bmp_file_header(std::fstream &in) {
	char byte[4];
	in.read(byte, 2);
	this->file_header.Signature = Byte::make_short(byte[0], byte[1]);
	in.read(byte, 4);
	this->file_header.FileSize = Byte::make_int(byte[0],byte[1],byte[2],byte[3]);
	in.read(byte, 4);
	this->file_header.Reserved = Byte::make_int(byte[0],byte[1],byte[2],byte[3]);
	in.read(byte, 4);
	this->file_header.DataOffset = Byte::make_int(byte[0],byte[1],byte[2],byte[3]);

	if(!Byte::compare_like_short(this->file_header.Signature, 'B', 'M')) {
		std::cerr << ERR_BMPIMAGE;
		return 0;
	}
	return 1;
}

void BMP::in_bmp_info_header(std::fstream &in) {
	char byte[4];
	in.read(byte,4);
	this->info_header.Size = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte,4);
	this->info_header.Width = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte,4);
	this->info_header.Height = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte,2);
	this->info_header.Planes = Byte::make_short(byte[0], byte[1]);
	in.read(byte,2);
	this->info_header.BitCount = Byte::make_short(byte[0], byte[1]);
	in.read(byte,4);
	this->info_header.Compression = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte,4);
	this->info_header.ImageSize = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte,4);
	this->info_header.XpixelsPerM = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte,4);
	this->info_header.YpixelsPerM = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte,4);
	this->info_header.ColourUsed = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	in.read(byte,4);
	this->info_header.ColorsImportant = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	if(this->info_header.Size >= 108) {
		in.read(byte, 4);
		this->info_header.RChannelBitmask = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		this->info_header.GChannelBitmask = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		this->info_header.BChannelBitmask = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		this->info_header.AChannelBitmask = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		this->info_header.ColorSpaceType = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		for (int i = 0; i < 9; ++i) {
			in.read(byte, 4);
			this->info_header.ColorSpaceEndpoints[i] = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		}
		in.read(byte, 4);
		this->info_header.GammaRchannel = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		this->info_header.GammaGchannel = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte, 4);
		this->info_header.GammaBchannel = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	}
	if(this->info_header.Size == 124){
		in.read(byte,4);
		this->info_header.Intent = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte,4);
		this->info_header.ICCProfileData = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte,4);
		this->info_header.ICCProfileSize = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
		in.read(byte,4);
		this->info_header.Reserved = Byte::make_int(byte[0], byte[1], byte[2], byte[3]);
	}

//	byte = Byte::get_byte(in, 4);
//	this->info_header.Width = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
//	byte = Byte::get_byte(in, 4);
//	this->info_header.Height = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
//	byte = Byte::get_byte(in, 2);
//	this->info_header.Planes = Byte::make_short(byte[1], byte[0]);
//	byte = Byte::get_byte(in, 2);
//	this->info_header.BitCount = Byte::make_short(byte[1], byte[0]);
//	byte = Byte::get_byte(in, 4);
//	this->info_header.Compression = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
//	byte = Byte::get_byte(in, 4);
//	this->info_header.ImageSize = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
//	byte = Byte::get_byte(in, 4);
//	this->info_header.XpixelsPerM = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
//	byte = Byte::get_byte(in, 4);
//	this->info_header.YpixelsPerM = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
//	byte = Byte::get_byte(in, 4);
//	this->info_header.ColourUsed = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
//	byte = Byte::get_byte(in, 4);
//	this->info_header.ColorsImportant = Byte::make_int(byte[3], byte[2], byte[1], byte[0]);
}

void BMP::in_bmp_palette(std::fstream &in) {
	if (BMPFileHeaderSIZE + this->info_header.Size != this->file_header.DataOffset) {
		int palette_size =
				this->file_header.DataOffset - (BMPFileHeaderSIZE + this->info_header.Size);
		this->have_palette = true;
		this->colors.resize(palette_size);
		for (int i = 0; i < palette_size / 4; ++i) {
			u_char b = in.get();
			u_char g = in.get();
			u_char r = in.get();
			u_char res = in.get();
			this->colors[i] = ColorItem(b, g, r, res);
		}
	} else {
		this->have_palette = false;
		this->colors.clear();
	}
}

void BMP::in_bmp_pixel_table(std::fstream &in) {

	switch(this->info_header.BitCount) {
		case 24:
			pixels.resize(this->info_header.Height);
			for (int i = 0; i < pixels.size(); ++i) {
				pixels[i].resize(this->info_header.Width);
			}
			this->cnt_extra_byte = (4-int(this->info_header.Width*3) % 4) % 4;
			for (int i = this->info_header.Height - 1; i >= 0; i--) {
				for (int j = 0; j < this->info_header.Width; ++j) {
					u_char b = in.get();
					u_char g = in.get();
					u_char r = in.get();
					this->pixels[i][j] = ColorItem(b, g, r, 0);
				}
				for (int j = 0; j < this->cnt_extra_byte; ++j) {
					in.get();
				}
			}
			break;
		default:
			return;
	}

//
//	if (this->info_header.BitCount != 24)
//		return;


}

bool BMP::input_image(std::string &name_file) {
	std::fstream in(name_file, std::ios_base::binary | std::ios_base::in);
	if (!in.is_open()) {
		std::cerr << ERR_NFILE;
		return false;
	}
	if(!in_bmp_file_header(in))
		return false;
	in_bmp_info_header(in);
	switch(this->info_header.BitCount){
		case 24:
			in_bmp_palette(in);
			in_bmp_pixel_table(in);
			break;
		default:
			std::cerr << ERR_IMAGE;
			in.close();
			return false;
	}
//	if (this->info_header.BitCount == 24) {
//
//	}
//	else {
//	}
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
		std::cerr << ERR_WIDTH;
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
		std::cerr << ERR_HEIGHT;
	}
}

bool
BMP::draw_square(int xpos, int ypos, int line_length, int line_width, ColorItem line_color, bool is_pour_over,
				 ColorItem square_color) {
	if (xpos < 0 || xpos >= this->info_header.Width || ypos < 0 || ypos >= this->info_header.Height) {
		std::cerr << ERR_XYPOS;
		return false;
	}
	if (line_length < 0 || xpos + line_length > this->info_header.Width ||
		ypos + line_length > this->info_header.Height || line_length < 2 * line_width) {
		std::cerr << ERR_LENGTH;
		return false;
	}
	if (line_width < 0) {
		std::cerr << ERR_WIDTH;
		return false;
	}
	// верхняя и нижняя линии
	for (int i = 0; i < line_width; ++i) {
		for (int j = 0; j < line_length; ++j) {
			this->pixels[ypos + i][xpos + j] = line_color;
			this->pixels[ypos + line_length - i - 1][xpos + j] = line_color;

		}
	}
	//боковые линии
	for (int i = line_width; i < line_length - line_width; ++i) {
		for (int j = 0; j < line_width; ++j) {
			this->pixels[ypos + i][xpos + j] = line_color;
			this->pixels[ypos + i][xpos + line_length - j - 1] = line_color;

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
		for (int j = 1; j <= line_width-1; ++j) {
			this->pixels[ypos + line_width + i + j][xpos + line_width + i] = line_color;
			this->pixels[ypos + line_width + i][xpos + line_width + i + j] = line_color;
		}
	}
	//побочная диагональ
	for (int i = 0; i < line_length - 2 * line_width; ++i) {
		this->pixels[ypos + line_length - line_width - i - 1][xpos + line_width + i] = line_color;
		for (int j = 1; j <= line_width - 1; ++j) {
			this->pixels[ypos + line_length - line_width - i - 1 + j][xpos + line_width + i] = line_color;
			this->pixels[ypos + line_length - line_width - i - 1][xpos + line_width + i - j] = line_color;
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
	for (int i = 0; i < this->info_header.Height; ++i) {
		for (int j = 0; j < this->info_header.Width; ++j) {
			switch (component) {
				case 'r':
					this->pixels[i][j].Red = num;
					break;
				case 'g':
					this->pixels[i][j].Green = num;
					break;
				case 'b':
					this->pixels[i][j].Blue = num;
					break;
			}
		}
	}
	return true;
}

bool BMP::rotate_fragment(int xlpos, int ylpos, int xrpos, int yrpos, int angle) {
	if (xlpos < 0 || xlpos >= this->info_header.Width || ylpos < 0 || ylpos >= this->info_header.Height) {
		std::cerr << ERR_LPOS;
		return false;
	}
	if (xrpos < 0 || xrpos >= this->info_header.Width || yrpos < 0 || yrpos >= this->info_header.Height) {
		std::cerr << ERR_RPOS;
		return false;
	}
	if (xlpos > xrpos || ylpos > yrpos) {
		std::cerr << ERR_LRPOS;
		return false;
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
	else{
		std::cerr << ERR_ANGLE;
		return false;
	}
	return true;
}

int BMP::getWidth() const {
	return this->info_header.Width;
}

int BMP::getHeight() const {
	return this->info_header.Height;
}

void
BMP::fill_circle(std::vector<std::pair<int, int>> &brd_ins, std::vector<std::pair<int, int>> &brd_out, int y,
				 ColorItem line_color){
	int delta_size = (brd_out.size() - brd_ins.size()) / 2;
	y++;
	for (int i = 1; i < delta_size; ++i) {
		for (int j = brd_out[i].first+1; j < brd_out[i].second; ++j) {
			this->pixels[y][j] = line_color;
		}
		y++;
	}
	int ind = 0;
	for (int i = delta_size; i < brd_out.size() - delta_size; ++i) {
		for (int j = brd_out[i].first+1; j < brd_ins[ind].first; ++j) {
			this->pixels[y][j] = line_color;
		}
		for (int j = brd_ins[ind].second+1; j < brd_out[i].second; ++j) {
			this->pixels[y][j] = line_color;
		}
		ind++;
		y++;
	}
	for (int i = brd_out.size()-delta_size; i < brd_out.size()-1; ++i) {
		for (int j = brd_out[i].first+1; j < brd_out[i].second; ++j) {
			this->pixels[y][j] = line_color;
		}
		y++;
	}

}

bool//делать -1 от пикселей, заданных пользователем
BMP::draw_circle_via_radius(int xpos, int ypos, int rad, int line_width, ColorItem line_color, bool is_pour_over,
							ColorItem circle_color) {
	if(xpos - rad - line_width + 1 < 0 || xpos + rad + line_width > this->info_header.Width ||
	ypos - rad - line_width + 1 < 0 || ypos + rad + line_width > this->info_header.Height){
		std::cerr << ERR_XYPOS;
		return false;
	}
	if(rad <= 0){
		std::cerr << ERR_RADIUS;
		return false;
	}
	if(line_width <= 0){
		std::cerr << ERR_WIDTH;
		return false;
	}
	draw_circle(xpos,ypos,rad,line_color);
	draw_circle(xpos,ypos,rad+line_width-1,line_color);
	auto borders_greater_circle_out = get_border_circle_out(xpos,rad+line_width-1, true);
	auto borders_less_circle_out = get_border_circle_out(xpos,rad, true);
	auto borders_less_circle_in = get_border_circle_in(xpos,rad, true);
	fill_circle(borders_less_circle_out,borders_greater_circle_out,ypos-rad-line_width+1,line_color);
	if(is_pour_over){
		for (int i = 1; i <= 2*rad; ++i) {
			for (int j = borders_less_circle_in[i].first+1; j < borders_less_circle_in[i].second; ++j) {
				this->pixels[ypos-rad+i][j] = circle_color;
			}
		}
	}
	return true;
}

bool BMP::draw_circle_via_square(int xposl, int yposl, int xposr, int yposr, int line_width, ColorItem line_color,
								 bool is_pour_over, ColorItem circle_color) {
	if(xposl >= xposr || yposl >= yposr || xposl < 0 || xposl >= this->info_header.Width ||
	xposr < 0 || xposr >= this->info_header.Width || yposl < 0 || yposl >= this->info_header.Height ||
	yposr < 0 || yposr >= this->info_header.Height){
		std::clog << ERR_XYPOS;
		return false;
	}
	if(xposr - xposl != yposr - yposl){
		std::clog << ERR_SQSHAPE;
		return false;
	}
	int xcentr = (xposr + xposl) / 2;
	int ycentr = (yposr + yposl) / 2;
	int radius = xcentr - xposl - line_width+1;
	if(radius < 0){
		std::clog << ERR_WIDTH;
		return false;
	}
	if((xposr - xposl) % 2 == 0)
		draw_circle_via_radius(xcentr,ycentr,radius,line_width,line_color,is_pour_over,circle_color);
	else{
		draw_circle(xcentr,ycentr,radius,line_color, false);
		draw_circle(xcentr,ycentr,radius+line_width-1,line_color, false);
		auto borders_greater_circle_out = get_border_circle_out(xcentr,radius+line_width-1, false);
		auto borders_less_circle_out = get_border_circle_out(xcentr,radius, false);
		auto borders_less_circle_in = get_border_circle_in(xcentr,radius, false);
		fill_circle(borders_less_circle_out,borders_greater_circle_out,ycentr-radius-line_width+1,line_color);
		if(is_pour_over){
			for (int i = 1; i <= 2*radius; ++i) {
				for (int j = borders_less_circle_in[i].first+1; j < borders_less_circle_in[i].second; ++j) {
					this->pixels[ycentr-radius+i][j] = circle_color;
				}
			}
		}
	}
	return true;
}


void BMP::draw_circle(int xcentr, int ycentr, int r, ColorItem color, bool have_center) {
	have_center = !have_center;
	int x = r;
	int y = 0;
	int radiusError = 1-x;
	while(x >= y){
		this->pixels[ycentr+have_center+y][xcentr+have_center+x] = color;
		this->pixels[ycentr+have_center+x][xcentr+have_center+y] = color;
		this->pixels[ycentr-y][xcentr+have_center+x] = color;
		this->pixels[ycentr-x][xcentr+have_center+y] = color;
		this->pixels[ycentr+have_center+y][xcentr-x] = color;
		this->pixels[ycentr+have_center+x][xcentr-y] = color;
		this->pixels[ycentr-y][xcentr-x] = color;
		this->pixels[ycentr-x][xcentr-y] = color;
		y++;
		if(radiusError < 0){
			radiusError += 2 * y + 1;
		} else{
			x--;
			radiusError += 2 * (y-x+1);
		}
	}
}

std::vector<std::pair<int, int>> BMP::get_border_circle_in(int xcentr, int r, bool have_center) const {
	have_center = !have_center;
	int x = r;
	int y = 0;
	int radiusError = 1-x;
	std::vector<std::pair<int,int>> borders(2*r+1+have_center, {-1e9,1e9});
	while(x >= y){

		borders[r+have_center+y].second = std::min(borders[r+have_center+y].second, xcentr+have_center+x);
		borders[r+have_center+x].second = std::min(borders[r+have_center+x].second, xcentr+have_center+y);
		borders[r-y].second = std::min(borders[r-y].second, xcentr+have_center+x);
		borders[r-x].second = std::min(borders[r-x].second, xcentr+have_center+y);
		borders[r+have_center+y].first = std::max(borders[r+have_center+y].first, xcentr-x);
		borders[r+have_center+x].first = std::max(borders[r+have_center+x].first, xcentr-y);
		borders[r-y].first = std::max(borders[r-y].first, xcentr-x);
		borders[r-x].first = std::max(borders[r-x].first, xcentr-y);
		y++;
		if(radiusError < 0){
			radiusError += 2 * y + 1;
		} else{
			x--;
			radiusError += 2 * (y-x+1);
		}
	}
	return borders;
}

std::vector<std::pair<int, int>> BMP::get_border_circle_out(int xcentr, int r, bool have_center) const {
	have_center = !have_center;
	int x = r;
	int y = 0;
	int radiusError = 1-x;
	std::vector<std::pair<int,int>> borders(2*r+1+have_center, {1e9,-1e9});
	while(x >= y){

		borders[r+have_center+y].second = std::max(borders[r+have_center+y].second, xcentr+have_center+x);
		borders[r+have_center+x].second = std::max(borders[r+have_center+x].second, xcentr+have_center+y);
		borders[r-y].second = std::max(borders[r-y].second, xcentr+have_center+x);
		borders[r-x].second = std::max(borders[r-x].second, xcentr+have_center+y);
		borders[r+have_center+y].first = std::min(borders[r+have_center+y].first, xcentr-x);
		borders[r+have_center+x].first = std::min(borders[r+have_center+x].first, xcentr-y);
		borders[r-y].first = std::min(borders[r-y].first, xcentr-x);
		borders[r-x].first = std::min(borders[r-x].first, xcentr-y);
		y++;
		if(radiusError < 0){
			radiusError += 2 * y + 1;
		} else{
			x--;
			radiusError += 2 * (y-x+1);
		}
	}
	return borders;
}

int BMP::getSize() const {
	return file_header.FileSize;
}

int BMP::getBitPerPixels() const {
	return info_header.BitCount;
}