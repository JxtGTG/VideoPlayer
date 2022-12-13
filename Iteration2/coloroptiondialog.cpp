#include "coloroptiondialog.h"
#include "ui_coloroptiondialog.h"

ColorOptionDialog::ColorOptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorOptionDialog)
{
    ui->setupUi(this);
}

ColorOptionDialog::~ColorOptionDialog()
{
    delete ui;
}

void ColorOptionDialog::on_close_clicked()
{
    this->close();
}
