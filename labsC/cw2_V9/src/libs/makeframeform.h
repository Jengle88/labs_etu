#ifndef MAKEFRAMEFORM_H
#define MAKEFRAMEFORM_H

#include <QDialog>
#include "bmp_libs/BMP_edit.h"
#include "../forms/ui_makeframeform.h"

namespace Ui {
class MakeFrameForm;
}

class MakeFrameForm : public QDialog
{
	BMP *bmp_image;
Q_OBJECT

public:
    explicit MakeFrameForm(QWidget *parent = nullptr, BMP *bmp_image = nullptr);
    ~MakeFrameForm();
	void init();

signals:
	void send_result(bool was_edited);
private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
private:
    Ui::MakeFrameForm *ui;
};

#endif // MAKEFRAMEFORM_H
