//#include "BMP_edit.h"
//#include <iostream>
////void testing_draw_square(BMP &bmp) {
////	bmp.draw_square(10, 10, 30, 4, CLR_RED, true, CLR_GREEN);//OK
////	bmp.draw_square(10, 10, 30, 4, CLR_RED);//OK
////	bmp.draw_square(-10, 10, 30, 4, CLR_RED);//BAD
////	bmp.draw_square(10, -10, 30, 4, CLR_RED);//BAD
////	bmp.draw_square(10, 10, -30, 4, CLR_RED);//BAD
////	bmp.draw_square(10, 10, 30, 40, CLR_RED);//BAD
////	bmp.draw_square(10, 10, 30, 15, CLR_RED);//OK
////}
////
////void testing_edit_component(BMP &bmp) {
////	bmp.edit_component('r', 0);//OK
////	bmp.edit_component('g', 255);//OK
////	bmp.edit_component('b', 0);//OK
////	bmp.edit_component('F', 255);//BAD
////
////}
//
//
////Vim: :%! xxd - показать HEX-содерж файла, :%! xxd -r - вернуть обычное представление
//int main() {
//	//BMP bmp;
//	//std::string name_file_input = "test3.bmp";
//	//BMPFileHeader bmph;
//	//BMPInfoHeader bmpi;
//	////FILE *f = fopen(name_file_input.c_str(), "rb");
//	//std::fstream in(name_file_input,std::ios_base::binary | std::ios_base::in);
//	//bmp.in_bmp_file_header(in);
//	//bmp.in_bmp_info_header(in);
//	//int z = 2;
//	BMP bmp;
//	std::string name_file_input = "test.bmp";
//	bmp.input_image(name_file_input);
//	bmp.setHeight(800);
//	bmp.setWidth(900);
//	std::string res = "result.bmp";
//	bmp.write_image(res);
//	return 0;
//
//}
