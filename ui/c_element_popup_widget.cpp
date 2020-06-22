#include "c_element_popup_widget.h"
#include "ui_c_element_popup_widget.h"

c_element_popup_widget::c_element_popup_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_element_popup_widget) {
    ui->setupUi(this);
    ui->widget->setStyleSheet(QString("widget{background-color : %1}").arg(app_color::grey_blue));
    ui->elem1->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/elements/fire_inked.png); height: 35px; width: auto;}"
                                "QCheckBox::indicator:checked {image: url(:/images/elements/fire_big.png); height: 35px; width: auto;} ");
    ui->elem2->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/elements/water_inked.png); height: 35px; width: auto;}"
                                "QCheckBox::indicator:checked {image: url(:/images/elements/water_big.png); height: 35px; width: auto;} ");
    ui->elem3->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/elements/earth_inked.png); height: 35px; width: auto;}"
                                "QCheckBox::indicator:checked {image: url(:/images/elements/earth_big.png); height: 35px; width: auto;} ");
    ui->elem4->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/elements/wind_inked.png); height: 35px; width: auto;}"
                                "QCheckBox::indicator:checked {image: url(:/images/elements/wind_big.png); height: 35px; width: auto;} ");
    ui->elem1->setCheckState(Qt::Checked);
    ui->elem2->setCheckState(Qt::Checked);
    ui->elem3->setCheckState(Qt::Checked);
    ui->elem4->setCheckState(Qt::Checked);
    QObject::connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&c_element_popup_widget::slot_accepted);
    QObject::connect(ui->elem1,&QCheckBox::stateChanged,this,&c_element_popup_widget::slot_add_element);
    QObject::connect(ui->elem2,&QCheckBox::stateChanged,this,&c_element_popup_widget::slot_add_element);
    QObject::connect(ui->elem3,&QCheckBox::stateChanged,this,&c_element_popup_widget::slot_add_element);
    QObject::connect(ui->elem4,&QCheckBox::stateChanged,this,&c_element_popup_widget::slot_add_element);
    number_checked = 0;
    checklist.push_back(ui->first_elem);
    checklist.push_back(ui->second_elem);
    checklist.push_back(ui->last_elem);

    list_element << "Feu" << "Eau" << "Terre" << "Air";

    frToEn_elem["Feu"] = "fire";
    frToEn_elem["Terre"] = "earth";
    frToEn_elem["Air"] = "wind";
    frToEn_elem["Eau"] = "water";
}

c_element_popup_widget::~c_element_popup_widget() {
    delete ui;
}

void c_element_popup_widget::setElems(QList<bool> elems) {

}

QList<bool> c_element_popup_widget::getElems() {

}

void c_element_popup_widget::slot_accepted() {

}

void c_element_popup_widget::slot_add_element() {
    if (chosen_elements.size() < 3) {
        if (static_cast<QCheckBox*>(sender()) == ui->elem1) {
            if (chosen_elements.contains("Feu")) {
                chosen_elements.removeOne("Feu");
            } else {
                chosen_elements.push_back("Feu");
            }
        } else if (static_cast<QCheckBox*>(sender()) == ui->elem2) {
            if (chosen_elements.contains("Eau")) {
                chosen_elements.removeOne("Eau");
            } else {
                chosen_elements.push_back("Eau");
            }
        } else if (static_cast<QCheckBox*>(sender()) == ui->elem3) {
            if (chosen_elements.contains("Terre")) {
                chosen_elements.removeOne("Terre");
            } else {
                chosen_elements.push_back("Terre");
            }
        } else if (static_cast<QCheckBox*>(sender()) == ui->elem4) {
            if (chosen_elements.contains("Air")) {
                chosen_elements.removeOne("Air");
            } else {
                chosen_elements.push_back("Air");
            }
        }
        number_checked++;
    }
    qDebug() << chosen_elements;
    updateView();
}

void c_element_popup_widget::updateView() {
    for (int i = 0; i < chosen_elements.size(); ++i) {
        checklist[i]->setCheckState(Qt::Checked);
        checklist[i]->setStyleSheet(QString("QCheckBox::indicator:checked {image: url(:/images/elements/%1_big.png); height: 35px; width: auto;}").arg(frToEn_elem[chosen_elements[i]]));
    }
    for (int i = chosen_elements.size(); i < 3; ++i) {
        checklist[i]->setStyleSheet("");
        checklist[i]->setCheckState(Qt::Unchecked);
    }
}


