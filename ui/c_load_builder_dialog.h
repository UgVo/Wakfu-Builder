#ifndef C_LOAD_BUILDER_DIALOG_H
#define C_LOAD_BUILDER_DIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include "utilities/c_dbmanager.h"
#include "utilities/c_save_builder_model.h"

namespace Ui {
class c_load_builder_dialog;
}

class c_load_builder_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit c_load_builder_dialog(c_dbmanager *manager,QWidget *parent = nullptr);
    ~c_load_builder_dialog();

    QString getCurrent_json() const;
    int getCurrent_id() const;

private:
    Ui::c_load_builder_dialog *ui;
    c_save_builder_model *model;
    QString current_json;
    int current_id;

public slots:
    void slot_table_cliked(const QModelIndex &index);
};

#endif // C_LOAD_BUILDER_DIALOG_H
