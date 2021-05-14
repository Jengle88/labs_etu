#ifndef CREATESQUAREFORM_H
#define CREATESQUAREFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include "bmp_libs/BMP_edit.h"
#include <QMessageBox>
#include "../forms/ui_createsquareform.h"
#include <iostream>

namespace Ui {
class CreateSquareForm;
}

class CreateSquareForm : public QDialog
{
	BMP *bmp_image;
	bool was_edited = false;
    Q_OBJECT

public:
    explicit CreateSquareForm(QWidget *parent, BMP *bmp_image);
    void init();
    void line_set_color(ColorItem color);
    void over_set_color(ColorItem color);
    ~CreateSquareForm();

	signals:
		void send_results(bool was_edited);

private slots:
    void on_buttonBox_accepted();
    void on_is_pure_over_stateChanged(int arg1);
    void on_buttonBox_rejected();

    void on_line_black_clicked();

    void on_line_white_clicked();

    void on_line_orange_clicked();

    void on_line_red_clicked();

    void on_line_green_clicked();

    void on_line_blue_clicked();

    void on_line_yellow_clicked();

    void on_line_pink_clicked();

    void on_over_black_clicked();

    void on_over_white_clicked();

    void on_over_red_clicked();

    void on_over_green_clicked();

    void on_over_blue_clicked();

    void on_over_yellow_clicked();

    void on_over_pink_clicked();

    void on_over_orange_clicked();

private:
    Ui::CreateSquareForm *ui;
};

#endif // CREATESQUAREFORM_H
