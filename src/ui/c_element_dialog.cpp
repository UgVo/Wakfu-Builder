#include "c_element_dialog.h"
#include "ui_c_element_dialog.h"

c_element_dialog::c_element_dialog(int number, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::c_element_dialog)
{
    ui->setupUi(this);
    _number = number;
    this->setStyleSheet(QString("QDialog#c_element_dialog{background-color : %1}").arg(app_color::grey_blue));
    ui->elem1->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/elements/fire_inked.png); height: 35px; width: auto;}"
                                "QCheckBox::indicator:checked {image: url(:/images/elements/fire_big.png); height: 35px; width: auto;} ");
    ui->elem2->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/elements/water_inked.png); height: 35px; width: auto;}"
                                "QCheckBox::indicator:checked {image: url(:/images/elements/water_big.png); height: 35px; width: auto;} ");
    ui->elem3->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/elements/earth_inked.png); height: 35px; width: auto;}"
                                "QCheckBox::indicator:checked {image: url(:/images/elements/earth_big.png); height: 35px; width: auto;} ");
    ui->elem4->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/elements/wind_inked.png); height: 35px; width: auto;}"
                                "QCheckBox::indicator:checked {image: url(:/images/elements/wind_big.png); height: 35px; width: auto;} ");
    QObject::connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&c_element_dialog::slot_accepted);
}

c_element_dialog::~c_element_dialog()
{
    delete ui;
}

void c_element_dialog::setElems(QList<bool> elems) {
    ui->elem1->setCheckState(elems.at(0)?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    ui->elem2->setCheckState(elems.at(1)?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    ui->elem3->setCheckState(elems.at(2)?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    ui->elem4->setCheckState(elems.at(3)?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
}

QList<bool> c_element_dialog::getElems() {
    return  {ui->elem1->checkState() == Qt::CheckState::Checked,
             ui->elem2->checkState() == Qt::CheckState::Checked,
             ui->elem3->checkState() == Qt::CheckState::Checked,
             ui->elem4->checkState() == Qt::CheckState::Checked};
}

void c_element_dialog::slot_accepted() {
    int i = 0;
    i = int(ui->elem1->checkState() == Qt::CheckState::Checked) +
            int(ui->elem2->checkState() == Qt::CheckState::Checked) +
            int(ui->elem3->checkState() == Qt::CheckState::Checked) +
            int(ui->elem4->checkState() == Qt::CheckState::Checked);
    if (i != _number) {
        QMessageBox::critical(this,"Erreur dans le nombre d'éléments",QString("%1 éléments devraient être sélectionés").arg(_number));
    } else {
        this->accept();
    }
}
