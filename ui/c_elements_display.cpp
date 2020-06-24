#include "c_elements_display.h"
#include "ui_c_elements_display.h"

QMap<QString,QString> c_elements_display::frToEn_elem = c_elements_display::set_frTo_En_elem();
QMap<QString,int> c_elements_display::frToId_elem = c_elements_display::set_frToId_elem();

c_elements_display::c_elements_display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_elements_display)
{
    ui->setupUi(this);
    this->setStyleSheet(QString("background-color : %1").arg(app_color::grey_blue));
    ui->widget->setStyleSheet(QString("background-color : %1; border-radius:3px;").arg(app_color::dark_blue));

    elems << "Feu" << "Eau" << "Terre" << "Air";

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->widget);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    chosen_elements << elems;
    label_list.push_back(ui->elem1);
    label_list.push_back(ui->elem2);
    label_list.push_back(ui->elem3);
    label_list.push_back(ui->elem4);

    update_view();
}

c_elements_display::~c_elements_display()
{
    delete ui;
}

QMap<QString,QString> c_elements_display::set_frTo_En_elem() {
    QMap<QString,QString> res;
    res["Feu"] = "fire";
    res["Terre"] = "earth";
    res["Air"] = "wind";
    res["Eau"] = "water";
    return res;
}

QMap<QString,int> c_elements_display::set_frToId_elem() {
    QMap<QString,int> res;
    res["Feu"] = 0;
    res["Eau"] = 1;
    res["Terre"] = 2;
    res["Air"] = 3;
    return res;
}

void c_elements_display::update_view() {
    for (int i = 0; i < 3; ++i) {
        label_list[i]->setPixmap(QPixmap(QString(":/images/elements/%1_big.png").arg(frToEn_elem[chosen_elements[i]])));
        label_list[i]->setBackgroundRole(QPalette::Base);
        label_list[i]->setScaledContents(true);
    }
    label_list[3]->setPixmap(QPixmap(QString(":/images/elements/%1_inked.png").arg(frToEn_elem[chosen_elements[3]])));
    label_list[3]->setBackgroundRole(QPalette::Base);
    label_list[3]->setScaledContents(true);
}

void c_elements_display::setElements(QList<QString> new_elems) {
    chosen_elements = new_elems;
    update_view();
    emit newElements(new_elems);
}

void c_elements_display::mouseDoubleClickEvent(QMouseEvent* /*event*/) {
    emit doubleCliked();
}
