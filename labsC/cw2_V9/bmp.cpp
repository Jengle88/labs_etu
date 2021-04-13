#include <iostream>
#include "BMP_edit.h"

/*
 * TODO:
 *  1) Построить квадрат с диагональю. Ширина диагонали вычисляется: sqrt(x) с округлением до ближ нечётного
 *  Из угла идёт середина ширины и смещение на +1 вверх и вправо
 *  Толщина линии диагонали должна совпадать с толщиной стороны
 *
 *
 */

void testing_draw_square(BMP &bmp) {
	bmp.draw_square(10, 10, 30, 4, CLR_RED, true, CLR_GREEN);//OK
	bmp.draw_square(10, 10, 30, 4, CLR_RED);//OK
	bmp.draw_square(-10, 10, 30, 4, CLR_RED);//BAD
	bmp.draw_square(10, -10, 30, 4, CLR_RED);//BAD
	bmp.draw_square(10, 10, -30, 4, CLR_RED);//BAD
	bmp.draw_square(10, 10, 30, 40, CLR_RED);//BAD
	bmp.draw_square(10, 10, 30, 15, CLR_RED);//OK
}

void testing_edit_component(BMP &bmp) {
	bmp.edit_component('r', 0);//OK
	bmp.edit_component('g', 255);//OK
	bmp.edit_component('b', 0);//OK
	bmp.edit_component('F', 255);//BAD

}

//Vim: :%! xxd - показать HEX-содерж файла, :%! xxd -r - вернуть обычное представление
int main() {

	BMP bmp;
	std::string name_file_input = "test.bmp";
	if (!bmp.input_picture(name_file_input))
		return 0;

	//bmp.draw_square(5,5,12,6,CLR_BLACK);
	//bmp.draw_square(5,5,6,3,CLR_RED);
	bmp.rotate_fragment(0, 0, bmp.getWidth() - 1, bmp.getHeight() - 1, 270);
	std::string name_file_output = "out.bmp";
	bmp.write_bmp(name_file_output);
	return 0;

}
