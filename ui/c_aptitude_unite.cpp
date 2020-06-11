#include "c_aptitude_unite.h"
#include "ui_c_aptitude_unite.h"
#include "c_aptitudes_display.h"

c_aptitude_unite::c_aptitude_unite(QString _text, int _max, QString image_name, QString _section, QWidget *_parent) :
    QWidget(_parent),
    ui(new Ui::c_aptitude_unite) {
    ui->setupUi(this);
    max = _max;
    type = _text;
    section = _section;
    ui->texte->setText(_text);
    value = 0;
    parent = static_cast<c_aptitudes_display*>(_parent);
    pack_increase = false;

    ui->value->setNum(value);
    ui->icon->setPixmap(QPixmap(QString(":/images/Aptitudes/%1.png").arg(image_name)));
    ui->icon->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon->setScaledContents(true);

    QIcon icon_plus;
    icon_plus.addPixmap(QPixmap(":/images/divers/plus.png"),QIcon::Normal);
    icon_plus.addPixmap(QPixmap(":/images/divers/plus_dis.png"),QIcon::Disabled);
    ui->pb_plus->setIcon(icon_plus);

    QIcon icon_minus;
    icon_minus.addPixmap(QPixmap(":/images/divers/moins.png"),QIcon::Normal);
    icon_minus.addPixmap(QPixmap(":/images/divers/moins_dis.png"),QIcon::Disabled);
    ui->pb_minus->setIcon(icon_minus);

    enable_minus(false);
    QObject::connect(ui->pb_plus,&QPushButton::clicked,this,&c_aptitude_unite::slot_plus_clicked);
    QObject::connect(ui->pb_minus,&QPushButton::clicked,this,&c_aptitude_unite::slot_minus_clicked);
}

c_aptitude_unite::~c_aptitude_unite()
{
    delete ui;
}

void c_aptitude_unite::enable_minus(bool enable) {
    ui->pb_minus->setEnabled(enable);
}

QString c_aptitude_unite::getType() const
{
    return type;
}

void c_aptitude_unite::setValue(int _value) {
    for (int i = 0; i < _value; ++i) {
        if (max == -1 || value < max) {
            int count = parent->decrease(section);
            if (count != -1) {
                value++;
                ui->value->setNum(value);
                enable_minus(true);
            }
        }
        if (value == max) {
            slot_setEnable_plus(false);
        }
    }
}

void c_aptitude_unite::slot_setEnable_plus(bool enable) {
    ui->pb_plus->setEnabled(enable);
}

void c_aptitude_unite::slot_plus_clicked() {
    int number = 1;
    if (pack_increase) {
        number = 10;
    }
    for (int i = 0; i < number; ++i) {
        if (max == -1 || value < max) {
            int count = parent->decrease(section);
            if (count != -1) {
                value++;
                ui->value->setNum(value);
                enable_minus(true);
            }
        }
        if (value == max) {
            slot_setEnable_plus(false);
        }
    }
    emit value_changed(value,type);
}

void c_aptitude_unite::slot_minus_clicked() {
    int number = 1;
    if (pack_increase) {
        number = 10;
    }
    for (int i = 0; i < number; ++i) {
        if (value > 0) {
            value--;
            parent->increase(section);
            ui->value->setNum(value);
            slot_setEnable_plus(true);
        }
        if (value == 0) {
            enable_minus(false);
        }
    }
    emit value_changed(value,type);
}

void c_aptitude_unite::shift_pressed(bool state) {
    pack_increase = state;
}

void c_aptitude_unite::reset() {
    value = 0;
    pack_increase = false;
    ui->value->setNum(value);
    slot_setEnable_plus(true);
    enable_minus(false);
}

//void c_aptitude_unite::keyPressEvent(QKeyEvent *event) {
//    if (event->key() == Qt::Key_Shift) {
//        pack_increase = true;
//    }
//}

//void c_aptitude_unite::keyReleaseEvent(QKeyEvent *event) {
//    if (event->key() == Qt::Key_Shift) {
//        pack_increase = false;
//    }
//}
