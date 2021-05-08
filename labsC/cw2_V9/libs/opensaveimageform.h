#ifndef OPENSAVEIMAGEFORM_H
#define OPENSAVEIMAGEFORM_H

#include <QDialog>
#include <QLineEdit>
#include "bmp_libs/BMP_edit.h"
#include <iostream>
#include "../forms/ui_opensaveimageform.h"

namespace Ui {
class OpenSaveImageForm;
}

class OpenSaveImageForm : public QDialog
{
    Q_OBJECT
public:
	explicit OpenSaveImageForm(QWidget *parent = nullptr, bool save_form = false);
    bool save_form;
    void init();
    ~OpenSaveImageForm();

    signals:
	void sendData(QString str);


private slots:
    void on_accept_clicked();

private:
    Ui::OpenSaveImageForm *ui;
};

#endif // OPENSAVEIMAGEFORM_H
