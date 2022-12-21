#ifndef COLOROPTIONDIALOG_H
#define COLOROPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ColorOptionDialog;
}

class ColorOptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorOptionDialog(QWidget *parent = 0);
    ~ColorOptionDialog();

public:
    Ui::ColorOptionDialog *ui;
private slots:
    void on_close_clicked();
};

#endif // COLOROPTIONDIALOG_H
