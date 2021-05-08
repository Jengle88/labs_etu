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
    ~CreateSquareForm();

	signals:
		void send_results(bool was_edited);

private slots:
    void on_buttonBox_accepted();
    void on_is_pure_over_stateChanged(int arg1);
    void on_buttonBox_rejected();

private:
    Ui::CreateSquareForm *ui;
};

#endif // CREATESQUAREFORM_H
