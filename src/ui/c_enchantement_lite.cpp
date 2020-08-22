#include "c_enchantement_lite.h"
#include "c_enchantement_lite.h"
#include "ui_c_enchantement_lite.h"

c_enchantement_lite::c_enchantement_lite(QWidget *parent, c_enchantement_effect effect) :
    QWidget(parent), ui(new Ui::c_enchantement_lite), _effect(effect)
{
    ui->setupUi(this);
    _id = effect.id();
    QPixmap pixmap;
    QIcon icon;
    switch (effect.color()) {
        case 1:
            pixmap.load(":/images/shard/shardRedFull.png");
            break;
        case 2:
            pixmap.load(":/images/shard/shardGreenFull.png");
            break;
        case 3:
            pixmap.load(":/images/shard/shardBlueFull.png");
            break;
    }
    icon.addPixmap(pixmap);
    ui->button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->button->setText(effect.effect());
    ui->button->setIcon(icon);
    ui->button->setStyleSheet(QString("Text-align:left; border-radius : 3px; border : 2px solid %1; background-color : %1; color : white;").arg(app_color::grey_blue_3));
    ui->button->setMinimumSize(QSize(200,0));
    QObject::connect(ui->button,&QToolButton::clicked,this,&c_enchantement_lite::slot_clicked);
}

c_enchantement_lite::~c_enchantement_lite()
{
    delete ui;
}

void c_enchantement_lite::slot_clicked() {
    slot_highLight(true);
    emit clicked(_id);
}

void c_enchantement_lite::slot_highLight(bool flag) {
    if (flag) {
        ui->button->setStyleSheet(QString("Text-align:left; border-radius : 3px; border : 2px solid white; background-color : %1; color : white;").arg(app_color::grey_blue_3));
        ui->button->setMinimumSize(QSize(220,0));
    } else {
        ui->button->setStyleSheet(QString("Text-align:left; border-radius : 3px; border : 2px solid %1; background-color : %1; color : white;").arg(app_color::grey_blue_3));
        ui->button->setMinimumSize(QSize(200,0));
    }
}

c_enchantement_effect c_enchantement_lite::effect() const
{
    return _effect;
}

int c_enchantement_lite::id() const
{
    return _id;
}
