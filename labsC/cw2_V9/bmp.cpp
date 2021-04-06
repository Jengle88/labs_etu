#include <iostream>
#include "BMP_edit.h"


//Vim: :%! xxd - показать HEX-содерж файла, :%! xxd -r - вернуть обычное представление
int main() {
	std::fstream in("test.bmp", std::ios_base::binary | std::ios_base::in);

	BMP bmp;
	bmp.input_picture(in);
	in.close();

	std::ofstream out("out2.bmp",std::ios_base::binary | std::ios_base::out);
	bmp.write_bmp(out);
	out.close();
	return 0;

}
