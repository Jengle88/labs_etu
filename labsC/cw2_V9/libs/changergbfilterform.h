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
	bool was_edited = false;
Q_OBJECT

public:
	explicit ChangeRGBFilterForm(QWidget *parent, BMP *bmp_image);
	void init();
	~ChangeRGBFilterForm();

signals:
	void send_results(bool was_edited);

private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

private:
	Ui::ChangeRGBFilterForm *ui;
};

#endif // CHANGERGBFILTERFORM_H
