#include <iostream>
#include "BMP_edit.h"


//Vim: :%! xxd - показать HEX-содерж файла, :%! xxd -r - вернуть обычное представление
int main() {

	BMP bmp;
	std::string name_file_input = "test.bmp";
	bmp.input_picture(name_file_input);

	std::string name_file_output = "out.bmp";
	bmp.write_bmp(name_file_output);
	return 0;

}
