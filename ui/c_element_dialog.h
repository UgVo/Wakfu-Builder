#ifndef C_ELEMENT_DIALOG_H
#define C_ELEMENT_DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "ui.h"

namespace Ui {
class c_element_dialog;
}

class c_element_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit c_element_dialog(int number, QWidget *parent = nullptr);
    ~c_element_dialog();

    void setElems(QList<bool> elems);
    QList<bool> getElems();

public slots:
    void slot_accepted();

private:
    Ui::c_element_dialog *ui;
    int _number;
};

#endif // C_ELEMENT_DIALOG_H
