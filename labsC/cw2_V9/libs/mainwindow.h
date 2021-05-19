#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bmp_libs/BMP_edit.h"
#include "createsquareform.h"
#include "changergbfilterform.h"
#include "rotatefragmentform.h"
#include "drawcircleform.h"
#include "../forms/ui_mainwindow.h"
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	QString name_file;
	QString name_temp_file;
	int image_border_pxls = 0;
	bool loaded_image = false;
	QPixmap *image;
	CreateSquareForm *squareForm;
	ChangeRGBFilterForm *rgbFilterForm;
	RotateFragmentForm *rotateFragForm;
	DrawCircleForm *drawCircleForm;
    Q_OBJECT
public:
	BMP bmp_image;
    BMP start_bmp_image;
    bool image_edited = false;
	MainWindow(QWidget *parent = nullptr);
	void try_save();
	void load_label_image(const std::string name_file);
    ~MainWindow();



private slots:
    void on_draw_square_clicked();
    void on_change_RGB_clicked();
    void on_rotate_fragment_clicked();
    void on_draw_circle_clicked();
    void on_load_image_clicked();
    void on_save_image_clicked();
    void on_reload_image_clicked();
    void on_pushButton_clicked();
    void on_reload_scale_clicked();

public slots:
	void receiveEditedImage(bool was_edited);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
