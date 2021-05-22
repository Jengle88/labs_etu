#ifndef CHANGERGBFILTERFORM_H
#define CHANGERGBFILTERFORM_H

#include <QDialog>
#include "bmp_libs/BMP_edit.h"
#include "../forms/ui_changergbfilterform.h"
#include <QMessageBox>


namespace Ui {
	class ChangeRGBFilterForm;
}

class ChangeRGBFilterForm : public QDialog
{
	BMP *bmp_image;
	Q_OBJECT

public:
	explicit ChangeRGBFilterForm(QWidget *parent, BMP *bmp_image);
	~ChangeRGBFilterForm();
	void init();

signals:
	void send_result(bool was_edited);

private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

private:
	Ui::ChangeRGBFilterForm *ui;
};

#endif // CHANGERGBFILTERFORM_H
