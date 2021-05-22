#ifndef ROTATEFRAGMENTFORM_H
#define ROTATEFRAGMENTFORM_H

#include <QDialog>
#include "bmp_libs/BMP_edit.h"
#include "../forms/ui_rotatefragmentform.h"

namespace Ui {
class RotateFragmentForm;
}

class RotateFragmentForm : public QDialog
{
	BMP *bmp_image;
    Q_OBJECT

public:
    explicit RotateFragmentForm(QWidget *parent, BMP *bmp_image);
	~RotateFragmentForm();
	void init();

signals:
	void send_result(bool was_edited);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::RotateFragmentForm *ui;
};

#endif // ROTATEFRAGMENTFORM_H
