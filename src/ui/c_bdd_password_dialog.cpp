#include "c_bdd_password_dialog.h"
#include "ui_c_bdd_password_dialog.h"

c_bdd_password_dialog::c_bdd_password_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::c_bdd_password_dialog)
{
    ui->setupUi(this);
}

c_bdd_password_dialog::~c_bdd_password_dialog()
{
    delete ui;
}

QString c_bdd_password_dialog::get_password() {
    return ui->lineEdit->text();
}
