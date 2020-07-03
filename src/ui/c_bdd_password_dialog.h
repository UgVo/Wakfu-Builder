#ifndef C_BDD_PASSWORD_DIALOG_H
#define C_BDD_PASSWORD_DIALOG_H

#include <QDialog>

namespace Ui {
class c_bdd_password_dialog;
}

class c_bdd_password_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit c_bdd_password_dialog(QWidget *parent = nullptr);
    ~c_bdd_password_dialog();
    QString get_password();

private:
    Ui::c_bdd_password_dialog *ui;
};

#endif // C_BDD_PASSWORD_DIALOG_H
