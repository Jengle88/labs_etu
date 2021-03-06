#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bmp_libs/BMP_edit.h"
#include "createsquareform.h"
#include "changergbfilterform.h"
#include "rotatefragmentform.h"
#include "makeframeform.h"
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
	BMP bmp_image;
	BMP start_bmp_image;
	bool loaded_image = false;
	bool image_edited = false;
	bool image_recover = true;
	int prev_label_h = 0;
	int prev_label_w = 0;
	QPixmap *image = nullptr;
	CreateSquareForm *squareForm;
	ChangeRGBFilterForm *rgbFilterForm;
	RotateFragmentForm *rotateFragForm;
	DrawCircleForm *drawCircleForm;
	MakeFrameForm *makeFrameForm;
    Q_OBJECT

	void try_save();

public:
	MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	void load_label_image(const std::string& name_file);
	std::string get_name_file();


private slots:
    void on_draw_square_clicked();
    void on_change_RGB_clicked();
    void on_rotate_fragment_clicked();
    void on_draw_circle_clicked();
    void on_load_image_clicked();
    void on_save_image_clicked();
    void on_reload_image_clicked();
    void on_reload_scale_clicked();
    void on_make_frame_clicked();
	void on_info_clicked();
	void receive_flag_edited_image(bool was_edited);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
