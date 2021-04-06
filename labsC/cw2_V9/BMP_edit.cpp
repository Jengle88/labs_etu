#include "BMP_edit.h"


void write_3_color(std::ofstream &out, const ColorItem &item) {
	out << item.rgbBlue << item.rgbGreen << item.rgbRed;
}

void write_4_color(std::ofstream &out, const ColorItem &item) {
	out << item.rgbBlue << item.rgbGreen << item.rgbRed << item.rgbReserved;
}

void BMP::in_bmp_file_header(std::fstream &in) {
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
	for (int i = 0; i < this->info_header.Height; ++i) {
		for (int j = 0; j < this->info_header.Width; ++j) {
			this->pixels[i][j] = {(u_char) in.get(), (u_char) in.get(),
								  (u_char) in.get()};
		}
		for (int j = 0; j < this->cnt_extra_byte; ++j) {
			in.get();
		}
	}
}

void BMP::input_picture(std::string &name_file) {
	std::fstream in(name_file, std::ios_base::binary | std::ios_base::in);
	in_bmp_file_header(in);
	in_bmp_info_header(in);
	if (this->info_header.BitCount == 24) {
		in_bmp_palette(in);
		in_bmp_pixel_table(in);
	}
	else {
		std::cout << "This image is not supported!";
	}
	in.close();
}

void BMP::write_bmp(std::string &name_file_output) const {
	if(this->info_header.BitCount != 24){
		return;
	}
	std::ofstream out(name_file_output,std::ios_base::binary | std::ios_base::out);

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
	for (int i = 0; i < this->info_header.Height; ++i) {
		for (int j = 0; j < this->info_header.Width; ++j) {
			write_3_color(out, this->pixels[i][j]);
		}
		for (int j = 0; j < this->cnt_extra_byte; ++j) {
			out << (u_char) 0;
		}
	}
	out.close();
}
