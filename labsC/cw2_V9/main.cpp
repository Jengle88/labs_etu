#include "libs/mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <sys/dir.h>



int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	w.load_label_image(w.get_name_file());
	return a.exec();
}
