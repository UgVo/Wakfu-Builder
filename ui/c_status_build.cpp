#include "c_status_build.h"
#include "ui_c_status_build.h"

c_status_build::c_status_build(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_status_build) {
    ui->setupUi(this);
    QPixmap image = QPixmap(":/images/portrait/aleat.png");
    ui->image_label->setPixmap(image);
    ui->image_label->setBackgroundRole(QPalette::Base);
    ui->image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->image_label->setScaledContents(true);

    setStyleSheet(QString("c_status_build{background-color: %1; color:white} QLabel{color:white;} QLineEdit{color : %2;} QSpinBox{color : %2;}").arg(app_color::grey_blue).arg(app_color::green_blue));
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->image_label);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->image_label->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));

    ui->guild_cb->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/65_inked.png);}"
                                "QCheckBox::indicator:checked {image: url(:/images/divers/65.png);} ");
    ui->guild_cb->setToolTip("Bonus de guilde");
    ui->nation_cb->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/6_inked.png);}"
                                "QCheckBox::indicator:checked {image: url(:/images/divers/6.png);} ");
    ui->nation_cb->setToolTip("Bonus de nation");
    ui->hm_cb->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/9_inked.png);}"
                                "QCheckBox::indicator:checked {image: url(:/images/divers/9.png);} ");
    ui->hm_cb->setToolTip("Bonus de Havre-monde");

    ui->bonuses->setStyleSheet(QString("background-color : %1; border-radius: 3px; color:white").arg(app_color::dark_blue));
    shadow = new QGraphicsDropShadowEffect(ui->bonuses);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->bonuses->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    ui->widget_name_lvl->setStyleSheet(QString("background-color : %1; border-radius: 3px").arg(app_color::dark_blue));
    shadow = new QGraphicsDropShadowEffect(ui->widget_name_lvl);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_name_lvl->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    QObject::connect(ui->build_lvl,&QSpinBox::editingFinished,this,&c_status_build::slot_enter_pressed);
    QObject::connect(ui->nation_cb,&QCheckBox::clicked,this,&c_status_build::slot_bonus_changed);
    QObject::connect(ui->guild_cb,&QCheckBox::clicked,this,&c_status_build::slot_bonus_changed);
    QObject::connect(ui->hm_cb,&QCheckBox::clicked,this,&c_status_build::slot_bonus_changed);

}

c_status_build::~c_status_build()
{
    delete ui;
}

void c_status_build::slot_enter_pressed() {
    ui->image_label->setFocus();
    emit lvl_changed(ui->build_lvl->value());
}

void c_status_build::setLvl(int lvl) {
    ui->build_lvl->setValue(lvl);
    emit lvl_changed(lvl);
}

void c_status_build::slot_bonus_changed() {
    QList<bool> res;
    res.push_back(ui->nation_cb->checkState()==Qt::CheckState::Checked);
    res.push_back(ui->guild_cb->checkState()==Qt::CheckState::Checked);
    res.push_back(ui->hm_cb->checkState()==Qt::CheckState::Checked);
    emit bonus_changed(res);
}

QString c_status_build::getName() {
    return ui->build_name->text();
}

int c_status_build::getLvl() {
    return ui->build_lvl->value();
}

void c_status_build::setName(QString name) {
    ui->build_name->setText(name);
}

bool c_status_build::isActivated_HM() {
    return ui->guild_cb->isChecked();
}

bool c_status_build::isActivated_Nation() {
    return ui->nation_cb->isChecked();
}

bool c_status_build::isActivated_Guilde() {
    return ui->guild_cb->isChecked();
}

void c_status_build::Activated_HM(bool state) {
    ui->hm_cb->setCheckState(state?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    slot_bonus_changed();
}

void c_status_build::Activated_Nation(bool state) {
    ui->nation_cb->setCheckState(state?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    slot_bonus_changed();
}

void c_status_build::Activated_Guilde(bool state) {
    ui->guild_cb->setCheckState(state?Qt::CheckState::Checked:Qt::CheckState::Unchecked);
    slot_bonus_changed();
}
