#include "c_load_builder_dialog.h"
#include "ui_c_load_builder_dialog.h"

c_save_builder_model *c_load_builder_dialog::model = nullptr;

c_load_builder_dialog::c_load_builder_dialog(c_dbmanager *manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::c_load_builder_dialog)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet(QString("QWidget#widget{background-color : %1;} QLabel{color : white;}").arg(app_color::grey_blue_2));
    this->setWindowTitle("Ouvrir un build");
    QSqlDatabase sql_db = manager->getDb();
    if (model == nullptr) {
        model = new c_save_builder_model(manager);
    }
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QObject::connect(ui->tableView,&QTableView::clicked,this,&c_load_builder_dialog::slot_table_cliked);
    ui->label_2->setStyleSheet("color:white;");
    ui->label_4->setStyleSheet("color:white;");
    ui->label_5->setStyleSheet("color:white;");
    ui->niveau->setText("");
    ui->niveau->setStyleSheet("color:white;");
    ui->name->setText("");
    ui->name->setStyleSheet("color:white;");
    ui->classe->setPixmap(QPixmap(":/images/portrait/aleat.png"));
    ui->label_4->hide();

    ui->tableView->verticalHeader()->setVisible(false);
    qDebug() << ui->tableView->styleSheet();
    ui->tableView->setFocusPolicy(Qt::NoFocus);
    ui->tableView->setShowGrid(false);
    ui->tableView->setStyleSheet(QString(" QTableView#tableView{"
                                         "   border : 1px solid white;"
                                         "   border-radius : 3px;"
                                         "   background-color : %1;"
                                         "} "
                                         "QTableView::item{"
                                         "   background-color : %1; "
                                         "   border-bottom : 1px solid #BBBBBB;"
                                         "   border-top : 1px solid #BBBBBB; "
                                         "}"
                                         "QTableView::item:selected {"
                                         "   color : white;"
                                         "   background-color: %2;	"
                                         "   border-bottom : 1px solid #BBBBBB;"
                                         "   border-top : 1px solid #BBBBBB; "
                                         "}                 "
                                         "QHeaderView::section { "
                                         "   background-color: %1; border : 1px solid %1; color : white;"
                                         "}"
                                         "QHeaderView {"
                                         "   border-bottom : 1px solid white;"
                                         "} ").arg(app_color::grey_blue).arg(app_color::green_blue));
    QObject::connect(ui->tableView,&QTableView::doubleClicked,this,&c_load_builder_dialog::slot_double_clicked);

    button_deleg = new c_button_delegate(ui->tableView);
    button_deleg->setModel(model);
    ui->tableView->setItemDelegate(button_deleg);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->setColumnWidth(0,30);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(2,193);
    ui->tableView->setColumnWidth(3,30);
    correct_scroll = false;
    ui->tableView->horizontalScrollBar()->setEnabled(false);
    QObject::connect(ui->tableView->horizontalScrollBar(),&QScrollBar::sliderMoved,this,&c_load_builder_dialog::slot_scrollbar_moved);
    QObject::connect(ui->tableView->horizontalScrollBar(),&QScrollBar::rangeChanged,this,&c_load_builder_dialog::slot_scrollbar_moved);
//    ui->tableView->horizontalHeader();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

c_load_builder_dialog::~c_load_builder_dialog() {
    delete ui;
}

QString c_load_builder_dialog::getCurrent_json() const {
    return current_json;
}

int c_load_builder_dialog::getCurrent_id() const {
    return current_id;
}

void c_load_builder_dialog::init_model(c_dbmanager *manager) {
    model = new c_save_builder_model(manager);
}

void c_load_builder_dialog::slot_table_cliked(const QModelIndex &index) {
    ui->tableView->selectionModel()->clearSelection();
    for (int i = 0; i < model->columnCount(index); ++i) {
        ui->tableView->selectionModel()->setCurrentIndex(model->index(index.row(),i),QItemSelectionModel::Select);
    }
    qDebug() << ui->tableView->verticalHeader()->size();
    ui->tableView->horizontalScrollBar()->setValue(0);
    //ui.textEdit->verticalScrollBar()->setValue(0);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    current_json = model->getJson(index);
    current_id = model->getId(index);
    ui->niveau->setNum(model->getLvl(index));
    ui->name->setText(model->getName(index));
    QString url = model->getUrlImage(index);
    ui->classe->setPixmap(QPixmap(url));
}

void c_load_builder_dialog::slot_double_clicked() {
    if (current_json.isEmpty()) return;
    accept();
}

void c_load_builder_dialog::slot_scrollbar_moved() {
    qDebug() << "slide moved" << correct_scroll;
    if (!correct_scroll) {
        ui->tableView->horizontalScrollBar()->setValue(0);
        correct_scroll = true;
    } else {
        correct_scroll = false;
    }
}

void c_load_builder_dialog::slot_debug() {
    qDebug() << "focused changed";
}
