#include <iostream>
#include "BMP_edit.h"


//void testing_draw_square(BMP &bmp) {
//	bmp.draw_square(10, 10, 30, 4, CLR_RED, true, CLR_GREEN);//OK
//	bmp.draw_square(10, 10, 30, 4, CLR_RED);//OK
//	bmp.draw_square(-10, 10, 30, 4, CLR_RED);//BAD
//	bmp.draw_square(10, -10, 30, 4, CLR_RED);//BAD
//	bmp.draw_square(10, 10, -30, 4, CLR_RED);//BAD
//	bmp.draw_square(10, 10, 30, 40, CLR_RED);//BAD
//	bmp.draw_square(10, 10, 30, 15, CLR_RED);//OK
//}
//
//void testing_edit_component(BMP &bmp) {
//	bmp.edit_component('r', 0);//OK
//	bmp.edit_component('g', 255);//OK
//	bmp.edit_component('b', 0);//OK
//	bmp.edit_component('F', 255);//BAD
//
//}

//Vim: :%! xxd - показать HEX-содерж файла, :%! xxd -r - вернуть обычное представление
int main() {

	BMP bmp;
	std::string name_file_input = "image24.bmp";
	if (!bmp.input_image(name_file_input))
		return 0;

//	bmp.draw_square(0,0,20,1,CLR_YELLOW, true, CLR_YELLOW);
//	bmp.draw_square(20,0,20,1,CLR_YELLOW, true, CLR_YELLOW);
//	bmp.draw_square(0,20,20,1,CLR_BLUE, true, CLR_BLUE);
//	bmp.draw_square(20,20,20,1,CLR_BLUE, true, CLR_BLUE);
	//bmp.rotate_fragment(0, 0, bmp.getWidth() - 1, bmp.getHeight() - 1, 270);
	//bmp.draw_circle_via_radius(38, 38, 1, 1, CLR_RED, true, CLR_BLUE);
	//bmp.draw_circle_via_radius(1, 1, 1, 1, CLR_RED, true, CLR_BLUE);
	bmp.draw_circle_via_square(35,36,39,39,1,CLR_BLACK, true, CLR_BLUE);
	//bmp.draw_circle_via_square(2,2,15,15,1,CLR_BLACK, true, CLR_BLUE);
	//bmp.draw_circle_via_radius(10,10,5,4,CLR_BLACK,true,CLR_BLUE);
//	bmp.draw_circle_via_radius(12,12,10,1,CLR_BLACK);
	std::string name_file_output = "out.bmp";
	bmp.write_bmp(name_file_output);
	return 0;

}
