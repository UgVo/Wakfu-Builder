#include "c_class_selection.h"
#include "ui_c_class_selection.h"

c_class_selection::c_class_selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_class_selection)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet(QString("QWidget#widget{background-color : %1; border-radius :3px; border : 1px solid white;} QLabel{color : white;}").arg(app_color::grey_blue));
    slot_update_genre();
    ui->checkBox->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/genre_fem.png);}"
                                "QCheckBox::indicator:checked {image: url(:/images/divers/genre_masc.png);}");
    QObject::connect(ui->checkBox,&QCheckBox::stateChanged,this,&c_class_selection::slot_update_genre);
    QObject::connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&c_class_selection::slot_canceled);
}

c_class_selection::~c_class_selection()
{
    delete ui;
}

void c_class_selection::setButtonStyle(QToolButton *pb) {
    pb->setAutoFillBackground(true);
    pb->setIconSize(QSize(76,75));
    pb->setAutoRaise(true);
    pb->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QObject::connect(pb,&QToolButton::clicked,this,&c_class_selection::slot_class_chosen);
}

void c_class_selection::slot_update_genre() {
    if (ui->checkBox->isChecked()) {
        ui->pb_10->setIcon(QIcon(":/images/portrait/10.png"));
        ui->pb_20->setIcon(QIcon(":/images/portrait/20.png"));
        ui->pb_30->setIcon(QIcon(":/images/portrait/30.png"));
        ui->pb_40->setIcon(QIcon(":/images/portrait/40.png"));
        ui->pb_50->setIcon(QIcon(":/images/portrait/50.png"));
        ui->pb_60->setIcon(QIcon(":/images/portrait/60.png"));
        ui->pb_70->setIcon(QIcon(":/images/portrait/70.png"));
        ui->pb_80->setIcon(QIcon(":/images/portrait/80.png"));
        ui->pb_90->setIcon(QIcon(":/images/portrait/90.png"));
        ui->pb_100->setIcon(QIcon(":/images/portrait/100.png"));
        ui->pb_110->setIcon(QIcon(":/images/portrait/110.png"));
        ui->pb_120->setIcon(QIcon(":/images/portrait/120.png"));
        ui->pb_130->setIcon(QIcon(":/images/portrait/130.png"));
        ui->pb_140->setIcon(QIcon(":/images/portrait/140.png"));
        ui->pb_150->setIcon(QIcon(":/images/portrait/150.png"));
        ui->pb_160->setIcon(QIcon(":/images/portrait/160.png"));
        ui->pb_180->setIcon(QIcon(":/images/portrait/180.png"));
        ui->pb_190->setIcon(QIcon(":/images/portrait/190.png"));
    } else {
        ui->pb_10->setIcon(QIcon(":/images/portrait/11.png"));
        ui->pb_20->setIcon(QIcon(":/images/portrait/21.png"));
        ui->pb_30->setIcon(QIcon(":/images/portrait/31.png"));
        ui->pb_40->setIcon(QIcon(":/images/portrait/41.png"));
        ui->pb_50->setIcon(QIcon(":/images/portrait/51.png"));
        ui->pb_60->setIcon(QIcon(":/images/portrait/61.png"));
        ui->pb_70->setIcon(QIcon(":/images/portrait/71.png"));
        ui->pb_80->setIcon(QIcon(":/images/portrait/81.png"));
        ui->pb_90->setIcon(QIcon(":/images/portrait/91.png"));
        ui->pb_100->setIcon(QIcon(":/images/portrait/101.png"));
        ui->pb_110->setIcon(QIcon(":/images/portrait/111.png"));
        ui->pb_120->setIcon(QIcon(":/images/portrait/121.png"));
        ui->pb_130->setIcon(QIcon(":/images/portrait/131.png"));
        ui->pb_140->setIcon(QIcon(":/images/portrait/141.png"));
        ui->pb_150->setIcon(QIcon(":/images/portrait/151.png"));
        ui->pb_160->setIcon(QIcon(":/images/portrait/161.png"));
        ui->pb_180->setIcon(QIcon(":/images/portrait/181.png"));
        ui->pb_190->setIcon(QIcon(":/images/portrait/191.png"));
    }
    setButtonStyle(ui->pb_10);
    setButtonStyle(ui->pb_20);
    setButtonStyle(ui->pb_30);
    setButtonStyle(ui->pb_40);
    setButtonStyle(ui->pb_50);
    setButtonStyle(ui->pb_60);
    setButtonStyle(ui->pb_70);
    setButtonStyle(ui->pb_80);
    setButtonStyle(ui->pb_90);
    setButtonStyle(ui->pb_100);
    setButtonStyle(ui->pb_110);
    setButtonStyle(ui->pb_120);
    setButtonStyle(ui->pb_130);
    setButtonStyle(ui->pb_140);
    setButtonStyle(ui->pb_150);
    setButtonStyle(ui->pb_160);
    setButtonStyle(ui->pb_180);
    setButtonStyle(ui->pb_190);
}

void c_class_selection::slot_class_chosen() {
    QToolButton *sender = static_cast<QToolButton*>(this->sender());
    int id = 0;
    if (sender == ui->pb_10) {
        id = 10;
    } else if (sender == ui->pb_20) {
        id = 20;
    } else if (sender == ui->pb_30) {
        id = 30;
    } else if (sender == ui->pb_40) {
        id = 40;
    } else if (sender == ui->pb_50) {
        id = 50;
    } else if (sender == ui->pb_60) {
        id = 60;
    } else if (sender == ui->pb_70) {
        id = 70;
    } else if (sender == ui->pb_80) {
        id = 80;
    } else if (sender == ui->pb_90) {
        id = 90;
    } else if (sender == ui->pb_100) {
        id = 100;
    } else if (sender == ui->pb_110) {
        id = 110;
    } else if (sender == ui->pb_120) {
        id = 120;
    }else if (sender == ui->pb_130) {
        id = 130;
    } else if (sender == ui->pb_140) {
        id = 140;
    } else if (sender == ui->pb_150) {
        id = 150;
    } else if (sender == ui->pb_160) {
        id = 160;
    } else if (sender == ui->pb_180) {
        id = 180;
    } else if (sender == ui->pb_190) {
        id = 190;
    }
    if (!ui->checkBox->isChecked()) {
        id++;
    }
    emit class_chosen(id);
}

void c_class_selection::slot_canceled() {
    emit rejected();
}
