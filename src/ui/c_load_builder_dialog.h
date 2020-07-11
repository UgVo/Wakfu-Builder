#ifndef C_LOAD_BUILDER_DIALOG_H
#define C_LOAD_BUILDER_DIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QPushButton>
#include <QScrollBar>
#include "utilities/c_dbmanager.h"
#include "utilities/c_save_builder_model.h"
#include "ui.h"
#include "c_button_delegate.h"

namespace Ui {
class c_load_builder_dialog;
}

class c_load_builder_dialog : public QDialog
{
    Q_OBJECT

    static c_save_builder_model *model;

public:
    explicit c_load_builder_dialog(c_dbmanager *manager,QWidget *parent = nullptr);
    ~c_load_builder_dialog();

    QString getCurrent_json() const;
    int getCurrent_id() const;

private:
    Ui::c_load_builder_dialog *ui;
//    c_save_builder_model *model;
    QString current_json;
    int current_id;
    c_button_delegate *button_deleg;
    bool correct_scroll;

    static void init_model(c_dbmanager *manager);

public slots:
    void slot_table_cliked(const QModelIndex &index);
    void slot_double_clicked();
    void slot_scrollbar_moved();
    void slot_debug();
};

#endif // C_LOAD_BUILDER_DIALOG_H
