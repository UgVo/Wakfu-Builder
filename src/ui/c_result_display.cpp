#include "c_result_display.h"
#include "ui_c_result_display.h"

c_result_display::c_result_display(c_dbmanager* _data_base, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_result_display) {
    ui->setupUi(this);
    this->setStyleSheet(QString("c_result_display{background-color : %1;} c_item_lite{background-color : %2}").arg(app_color::grey_blue).arg(app_color::dark_blue));
    ui->page_indicator->setStyleSheet("color:white");
    while (ui->stackedWidget->count()) {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    }
    data_base = _data_base;
    stackedWidget = new QStackedWidget;
    stacklayout = new QStackedLayout;
    stacklayout->setStackingMode(QStackedLayout::StackAll);
    loading = new QLabel;
    movie = new QMovie(":/images/divers/Eliacube.gif");
    loading->setMovie(movie);
    loading->setAlignment(Qt::AlignCenter);
    movie->start();

    static_cast<QVBoxLayout*>(layout())->insertLayout(0,stacklayout);
    stacklayout->addWidget(loading);
    stacklayout->addWidget(stackedWidget);
    setUpWidget();
    current_page = 0;
    used_page_number = 0;
    number_items = 0;
    QObject::connect(ui->next,&QPushButton::pressed,this,&c_result_display::slot_next);
    QObject::connect(ui->preview,&QPushButton::pressed,this,&c_result_display::slot_preview);

    ui->next->setIcon(QIcon(":/images/divers/next_arrow.png"));
    ui->preview->setIcon(QIcon(":/images/divers/preview_arrow.png"));

    sorted = false;
    loading->hide();
}

c_result_display::~c_result_display() {
    delete ui;
}


void c_result_display::slot_new_search_result(QList<int> item_id_list) {
    empty_pages();
    sorted = false;
    loading->show();
    id_list = item_id_list;
    std::reverse(id_list.begin(), id_list.end());
    current_page = 0;
    stackedWidget->setCurrentIndex(current_page);
    used_page_number = qCeil(qreal(item_id_list.size())/qreal((ROW_PER_PAGE*COLUMN_PER_PAGE))) - 1;
    number_items = item_id_list.size();
    fill_page(0);
}

void c_result_display::slot_new_search_result_sorted(QList<int> item_id_list) {
    empty_pages();
    sorted = true;
    loading->show();
    id_list = item_id_list;
    current_page = 0;
    stackedWidget->setCurrentIndex(current_page);
    used_page_number = qCeil(qreal(item_id_list.size())/qreal((ROW_PER_PAGE*COLUMN_PER_PAGE))) - 1;
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
    QElapsedTimer timer,timer2;
    loading->show();
    QList<int> sub_item_id_list;
    sub_item_id_list = id_list.mid(ROW_PER_PAGE*COLUMN_PER_PAGE*page,ROW_PER_PAGE*COLUMN_PER_PAGE);
    QList<c_item> item_list;
    QList<c_item_lite*> item_lite_list;
    timer.start();
    if (!sorted) {
        item_list = data_base->getItems(sub_item_id_list);
    } else {
        for ( int i = 0; i < sub_item_id_list.size(); ++i) {
            item_list.append(data_base->getItems(sub_item_id_list.mid(i,1)));
        }
    }
    qDebug() << "getItem from data base :" << timer.elapsed() << "ms";
    timer.restart();
    int n = 4;
    int size = item_list.size();
    int done = (size/n)*n;
    for(int i = 0; i < size/n; ++i) {
        movie->jumpToNextFrame();
        timer2.restart();
        item_lite_list.push_back(new c_item_lite(data_base,item_list.at(n*i),this));
        QObject::connect(item_lite_list.last(),&c_item_lite::item_doubleCliked,this,&c_result_display::slot_item_doubleCliked);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hovered,this,&c_result_display::slot_item_hovered);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hide,this,&c_result_display::slot_item_hide);
        item_lite_list.push_back(new c_item_lite(data_base,item_list.at(n*i+1),this));
        QObject::connect(item_lite_list.last(),&c_item_lite::item_doubleCliked,this,&c_result_display::slot_item_doubleCliked);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hovered,this,&c_result_display::slot_item_hovered);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hide,this,&c_result_display::slot_item_hide);
        item_lite_list.push_back(new c_item_lite(data_base,item_list.at(n*i+2),this));
        QObject::connect(item_lite_list.last(),&c_item_lite::item_doubleCliked,this,&c_result_display::slot_item_doubleCliked);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hovered,this,&c_result_display::slot_item_hovered);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hide,this,&c_result_display::slot_item_hide);
        item_lite_list.push_back(new c_item_lite(data_base,item_list.at(n*i+3),this));
        QObject::connect(item_lite_list.last(),&c_item_lite::item_doubleCliked,this,&c_result_display::slot_item_doubleCliked);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hovered,this,&c_result_display::slot_item_hovered);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hide,this,&c_result_display::slot_item_hide);
        QThread::msleep(1);
    }
    for (int i = done; i < size; ++i ) {
        item_lite_list.push_back(new c_item_lite(data_base,item_list.at(i),this));
        QObject::connect(item_lite_list.last(),&c_item_lite::item_doubleCliked,this,&c_result_display::slot_item_doubleCliked);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hovered,this,&c_result_display::slot_item_hovered);
        QObject::connect(item_lite_list.last(),&c_item_lite::item_hide,this,&c_result_display::slot_item_hide);
        QThread::msleep(1);
    }
    qDebug() << "Creation of item_lite :" << timer.elapsed() << "ms";
    timer.restart();
    int i = 0;
    for(int j = 0; j < item_list.size(); ++j) {
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(item_lite_list.at(j));
        shadow->setColor(QColor(91, 108, 142, 180));
        shadow->setOffset(2,2);
        item_lite_list.at(j)->setGraphicsEffect(shadow);
        static_cast<QGridLayout*>(stackedWidget->widget(page)->layout())->addWidget(item_lite_list.at(j),i/COLUMN_PER_PAGE,i%COLUMN_PER_PAGE);
        ++i;
    }
    qDebug() << "Creation of shadows and added to the widget :" << timer.elapsed() << "ms : " << stackedWidget->widget(page)->layout()->count() << " elements";
    timer.restart();
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

void c_result_display::hide_widgets() {
    for (int i = 0; i < 1; ++i) {
        int count = stackedWidget->widget(i)->layout()->count();
        for (int j = 0; j < count; ++j) {
            QWidget *widget = stackedWidget->widget(i)->layout()->itemAt(j)->widget();
            if (widget != nullptr) {
                widget->setVisible(false);
            }
        }
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

c_item_lite *c_result_display::generate_item_lite(c_item item) {
    c_item_lite *item_lite = new c_item_lite(nullptr,item);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(item_lite);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    item_lite->setGraphicsEffect(shadow);
    return item_lite;
}

void c_result_display::resizeEvent(QResizeEvent *event) {
    if (this->rect().width() < 600) {
        COLUMN_PER_PAGE = 2;
        slot_new_search_result(id_list);
    } else {
        COLUMN_PER_PAGE = 3;
        slot_new_search_result(id_list);
    }
}

void c_result_display::refreshView() {
    empty_page(current_page);
    fill_page(current_page);
}

void c_result_display::slot_next() {
    if (current_page < used_page_number) {
        current_page++;
        fill_page(current_page);
        empty_page(current_page-1);
        stackedWidget->setCurrentIndex(current_page);
    }
    int upper_bound = (current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+COLUMN_PER_PAGE*ROW_PER_PAGE > number_items ? number_items : current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+COLUMN_PER_PAGE*ROW_PER_PAGE);
    ui->page_indicator->setText(QString("%1 - %2 de %3").arg(number_items?current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+1:0).arg(upper_bound).arg(number_items));
}

void c_result_display::slot_preview() {
    if (current_page > 0) {
        current_page--;
        fill_page(current_page);
        empty_page(current_page+1);
        stackedWidget->setCurrentIndex(current_page);
    }
    int upper_bound = (current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+COLUMN_PER_PAGE*ROW_PER_PAGE > number_items ? number_items : current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+COLUMN_PER_PAGE*ROW_PER_PAGE);
    ui->page_indicator->setText(QString("%1 - %2 de %3").arg(number_items?current_page*COLUMN_PER_PAGE*ROW_PER_PAGE+1:0).arg(upper_bound).arg(number_items));
}

void c_result_display::slot_item_doubleCliked(c_item item) {
    emit item_doubleCliked(item);
}

void c_result_display::slot_item_hovered(QString type, QPoint pos) {
    emit item_hovered(type,pos);
}

void c_result_display::slot_item_hide(QString type) {
    emit item_hide(type);
}
