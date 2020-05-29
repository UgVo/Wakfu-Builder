#include "c_result_display.h"
#include "ui_c_result_display.h"

c_result_display::c_result_display(c_dbmanager* _data_base, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_result_display) {
    ui->setupUi(this);
    this->setStyleSheet(QString("c_result_display{background-color : %1} c_item_lite{background-color : %2}").arg(app_color::grey_blue).arg(app_color::dark_blue));
    while (ui->stackedWidget->count()) {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    }
    data_base = _data_base;
    stackedWidget = new QStackedWidget;
    stacklayout = new QStackedLayout;
    stacklayout->setStackingMode(QStackedLayout::StackAll);
    loading = new QLabel;
    movie = new QMovie("images/divers/LameDifferentBalloonfish-small.gif");
    loading->setMovie(movie);
    loading->setAlignment(Qt::AlignCenter);
    movie->start();

    static_cast<QVBoxLayout*>(layout())->insertLayout(0,stacklayout);
    stacklayout->addWidget(loading);
    stacklayout->addWidget(stackedWidget);
    setUpWidget();
    current_page = 0;
    QObject::connect(ui->next,&QPushButton::pressed,this,&c_result_display::slot_next);
    QObject::connect(ui->preview,&QPushButton::pressed,this,&c_result_display::slot_preview);

    ui->next->setIcon(QIcon("images/divers/next_arrow.png"));
    ui->preview->setIcon(QIcon("images/divers/preview_arrow.png"));

    loading->hide();
}

c_result_display::~c_result_display() {
    delete ui;
}


void c_result_display::slot_new_search_result(QList<int> item_id_list) {
    empty_pages();
    id_list = item_id_list;
    std::reverse(id_list.begin(), id_list.end());
    current_page = 0;
    stackedWidget->setCurrentIndex(current_page);
    used_page_number = item_id_list.size()/(ROW_PER_PAGE*COLUMN_PER_PAGE);
    number_items = item_id_list.size();
    fill_page(0);
}

void c_result_display::setUpWidget() {
    QList<int> item_list_id = data_base->getItemListId();
    int item_number = item_list_id.size();
    page_number = item_number/(ROW_PER_PAGE*COLUMN_PER_PAGE) + 1;
    create_page(page_number);
}

void c_result_display::create_page(int number) {
    for (int i = 0; i < number; ++i) {
        QWidget *widget = new QWidget;
        QGridLayout *layout = new QGridLayout;
        widget->setLayout(layout);
        layout->setMargin(0);
        stackedWidget->addWidget(widget);
    }
}

void c_result_display::fill_page(int page) {
    loading->show();
    QList<int> sub_item_id_list;
    sub_item_id_list = id_list.mid(ROW_PER_PAGE*COLUMN_PER_PAGE*page,ROW_PER_PAGE*COLUMN_PER_PAGE);
    QList<c_item> item_list;
    QList<c_item_lite*> item_lite_list;
    item_list = data_base->getItems(sub_item_id_list);
    for(int i = 0; i < item_list.size(); ++i) {
        item_lite_list.push_back(new c_item_lite(data_base,item_list.at(i),this));
        QObject::connect(item_lite_list.last(),&c_item_lite::item_doubleCliked,this,&c_result_display::slot_item_doubleCliked);
    }
    int i = 0;
    for(int j = 0; j < item_list.size(); ++j) {
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(item_lite_list.at(j));
        shadow->setColor(QColor(91, 108, 142, 180));
        shadow->setOffset(2,2);
        item_lite_list.at(j)->setGraphicsEffect(shadow);
        static_cast<QGridLayout*>(stackedWidget->widget(page)->layout())->addWidget(item_lite_list.at(j),i/COLUMN_PER_PAGE,i%COLUMN_PER_PAGE);
        ++i;
    }
    QSpacerItem *spacer = new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
    static_cast<QGridLayout*>(stackedWidget->widget(page)->layout())->addItem(spacer,ROW_PER_PAGE,COLUMN_PER_PAGE);
    stackedWidget->widget(page)->show();
    ui->page_indicator->setText(QString("%1 - %2 de %3").arg(current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+1).arg(sub_item_id_list.size()+page*COLUMN_PER_PAGE*ROW_PER_PAGE).arg(number_items));
    loading->hide();
}


void c_result_display::empty_pages() {
    for (int i = 0; i < 1; ++i) {
        clearLayout(stackedWidget->widget(i)->layout());
    }
}

void c_result_display::empty_page(int page) {
    if (page >= 0) {
        clearLayout(stackedWidget->widget(page)->layout());
    }
}


void c_result_display::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (deleteWidgets) {
            if (QWidget* widget = item->widget()) {
                widget->deleteLater();
            }
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

void c_result_display::slot_next() {
    qDebug() << current_page << used_page_number;
    if (current_page < used_page_number) {
        current_page++;
        fill_page(current_page);
        empty_page(current_page-1);
        stackedWidget->setCurrentIndex(current_page);
    }
    int upper_bound = (current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+COLUMN_PER_PAGE*ROW_PER_PAGE > number_items ? number_items : current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+COLUMN_PER_PAGE*ROW_PER_PAGE);
    ui->page_indicator->setText(QString("%1 - %2 de %3").arg(current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+1).arg(upper_bound).arg(number_items));
}

void c_result_display::slot_preview() {
    qDebug() << current_page;
    if (current_page > 0) {
        current_page--;
        fill_page(current_page);
        empty_page(current_page+1);
        stackedWidget->setCurrentIndex(current_page);
    }
    int upper_bound = (current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+COLUMN_PER_PAGE*ROW_PER_PAGE > number_items ? number_items : current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+COLUMN_PER_PAGE*ROW_PER_PAGE);
    ui->page_indicator->setText(QString("%1 - %2 de %3").arg(current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+1).arg(upper_bound).arg(number_items));
}

void c_result_display::slot_item_doubleCliked(c_item item) {
    emit item_doubleCliked(item);
}
