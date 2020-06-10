#include "c_load_builder_dialog.h"
#include "ui_c_load_builder_dialog.h"

c_load_builder_dialog::c_load_builder_dialog(c_dbmanager *manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::c_load_builder_dialog)
{
    ui->setupUi(this);
    QSqlDatabase sql_db = manager->getDb();
    model = new c_save_builder_model(manager);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    QObject::connect(ui->tableView,&QTableView::clicked,this,&c_load_builder_dialog::slot_table_cliked);
}

c_load_builder_dialog::~c_load_builder_dialog()
{
    delete ui;
}

QString c_load_builder_dialog::getCurrent_json() const {
    return current_json;
}

int c_load_builder_dialog::getCurrent_id() const {
    return current_id;
}

void c_load_builder_dialog::slot_table_cliked(const QModelIndex &index) {
    current_json = model->getJson(index);
    current_id = model->getId(index);

}
