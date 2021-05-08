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
	~DrawCircleForm();

signals:
	void send_results(bool was_edited);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_drawSquare_clicked();

    void on_drawPointRad_clicked();

    void on_is_pure_over_stateChanged(int arg1);

private:
    Ui::DrawCircleForm *ui;
};

#endif // DRAWCIRCLEFORM_H
