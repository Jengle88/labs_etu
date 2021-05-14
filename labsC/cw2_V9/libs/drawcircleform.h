#ifndef DRAWCIRCLEFORM_H
#define DRAWCIRCLEFORM_H

#include <QDialog>
#include "../forms/ui_drawcircleform.h"
#include "bmp_libs/BMP_edit.h"

namespace Ui {
class DrawCircleForm;
}

class DrawCircleForm : public QDialog
{
	BMP *bmp_image;
	bool was_edited = false;
    Q_OBJECT
public:
    explicit DrawCircleForm(QWidget *parent, BMP *bmp_image);
	void init();
	void line_set_color(ColorItem color);
	void over_set_color(ColorItem color);
	~DrawCircleForm();

signals:
	void send_results(bool was_edited);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_drawSquare_clicked();
    void on_drawPointRad_clicked();
    void on_is_pure_over_stateChanged(int arg1);
    void on_line_black_clicked();

    void on_line_white_clicked();

    void on_line_red_clicked();

    void on_line_green_clicked();

    void on_line_blue_clicked();

    void on_line_yellow_clicked();

    void on_line_pink_clicked();

    void on_line_orange_clicked();

    void on_over_black_clicked();

    void on_over_white_clicked();

    void on_over_red_clicked();

    void on_over_green_clicked();

    void on_over_blue_clicked();

    void on_over_yellow_clicked();

    void on_over_pink_clicked();

    void on_over_orange_clicked();

private:
    Ui::DrawCircleForm *ui;
};

#endif // DRAWCIRCLEFORM_H
