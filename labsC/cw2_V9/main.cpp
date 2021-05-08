#include "libs/mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <sys/dir.h>



int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.setFixedSize(800, 610);
	w.show();
	return a.exec();
}
