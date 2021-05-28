#include "libs/mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <sys/dir.h>
#include "bmp_libs/BMP_edit.h"


int main(int argc, char *argv[]) {
//	BMP bmp;
//	bmp.input_image("examples/test.bmp");
//	bmp.set_height(25);
//	bmp.set_width(25);
//	bmp.make_frame(2,CLR_BLACK);
//	bmp.write_image("result.bmp");
//	return 0;

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	if(!w.get_name_file().empty())
		w.load_label_image(w.get_name_file());
	return a.exec();
}
