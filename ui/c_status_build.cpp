#include "c_status_build.h"
#include "ui_c_status_build.h"

c_status_build::c_status_build(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_status_build) {
    ui->setupUi(this);
    QPixmap image = QPixmap("images/portrait/190.png");
    ui->image_label->setPixmap(image);
    ui->image_label->setBackgroundRole(QPalette::Base);
    ui->image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->image_label->setScaledContents(true);

    //ui->image_classe->setStyleSheet(QString("QWidget{background-color : %1; border: 1px solid %1; border-radius : 3px;}").arg(app_color::grey_blue));
    setStyleSheet(QString("c_status_build{background-color: %1; color:white} QLabel{color:white;} QLineEdit{color : %2;} QSpinBox{color : %2;}").arg(app_color::grey_blue).arg(app_color::green_blue));
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->image_label);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->image_label->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));

    ui->guild_cb->setStyleSheet("QCheckBox::indicator:unchecked {image: url(images/divers/65_dark.png);}"
                                "QCheckBox::indicator:checked {image: url(images/divers/65_light.png);} ");
    ui->guild_cb->setToolTip("Bonus de guilde");
    ui->nation_cb->setStyleSheet("QCheckBox::indicator:unchecked {image: url(images/divers/6_dark.png);}"
                                "QCheckBox::indicator:checked {image: url(images/divers/6_light.png);} ");
    ui->nation_cb->setToolTip("Bonus de nation");
    ui->hm_cb->setStyleSheet("QCheckBox::indicator:unchecked {image: url(images/divers/9_dark.png);}"
                                "QCheckBox::indicator:checked {image: url(images/divers/9_light.png);} ");
    ui->hm_cb->setToolTip("Bonus de nation");

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

}

c_status_build::~c_status_build()
{
    delete ui;
}

void c_status_build::slot_enter_pressed() {
    ui->image_label->setFocus();
    emit lvl_changed(ui->build_lvl->value());
}
