#include "c_item_display.h"
#include "ui_c_item_display.h"

//const QString c_item_display::color_background = "#6A8BA8";
//const QString c_item_display::color_foreground = "#305A7F";
const QString c_item_display::color_foreground = "#6A8BA8";
const QString c_item_display::color_background = "#305A7F";
const QList<QString> c_item_display::color_rarity = {"ffffff","ffffff","28f18b","fd8e39","fede71","fd87ba","8fc7e2","fd87ba"};

c_item_display::c_item_display(c_item item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_item_display),
    _item(item)
{
    ui->setupUi(this);

    updateView();
    data_complete = false;
}

QString c_item_display::replace_image(QString text) {
    text.replace("Lumière","<img src='images/elements/smallLIGHT.png'>");
    text.replace("Feu","<img src='images/elements/smallFIRE.png'>");
    text.replace("Terre","<img src='images/elements/smallEARTH.png'>");
    text.replace("Eau","<img src='images/elements/smallWATER.png'>");
    text.replace("Air","<img src='images/elements/smallAIR.png'>");
    text.replace("ally","<img src='images/divers/ally.png'>");
    return text;
}

c_item_display::~c_item_display() {
    delete ui;
}

void c_item_display::completeData(c_dbmanager *manager) {
    if (!data_complete) {
        _item.setUseEffects(manager->getUseEffectFromItemId(_item.getId()));
        _item.setEquipEffets(manager->getEquipEffectFromItemId(_item.getId()));
        updateView();
        data_complete = true;
    }
}

void c_item_display::updateView() {
    size_layout = 0;

    QList<QString> color_rarity = {"ffffff","ffffff","28f18b","fd8e39","fede71","fd87ba","8fc7e2","fd87ba"};

    this->setStyleSheet(QString("QWidget#c_item_display {background-color: %1;} img {vertical-align:middle;}").arg(app_color::dark_blue));
    QFont font = ui->item_name->font();
    QFont font_bold = font;
    font_bold.setBold(true);


    QPalette palette = ui->item_name->palette();
    ui->item_name->setFont(font);
    ui->item_name->setText(_item.getName());
    ui->item_name->setStyleSheet(QString("color:%1;").arg(app_color::color_rarity.at(_item.getRarity())));

    palette = ui->item_lvl->palette();
    palette.setColor(ui->item_lvl->foregroundRole(), Qt::white);
    ui->item_lvl->setPalette(palette);
    ui->item_lvl->setFont(font);
    ui->item_lvl->setText(QString("Niv.%1").arg(_item.getLvl()));

    palette = ui->item_type->palette();
    palette.setColor(ui->item_type->foregroundRole(), Qt::white);
    ui->item_type->setPalette(palette);
    ui->item_type->setFont(font);
    ui->item_type->setText(QString("[%1]").arg(_item.getType().getTitle()));

    ui->line_widget->setStyleSheet(QString("QWidget#line_widget {background-color: white;} "));

    QPixmap pixmap(QString("images/items/%1.png").arg(_item.getGfxId()));
    ui->item_image->setPixmap(pixmap);
    ui->item_image->setBackgroundRole(QPalette::Base);
    ui->item_image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->item_image->setScaledContents(true);

    ui->background_item->setStyleSheet(QString("QWidget#background_item {background-image: url(images/divers/NONE.png) ;}"));

    QLabel *label;
    if (_item.getUseEffects().size()) {
        ui->use_label->setText(QString("A l'utilisation :"));
        ui->use_label->setFont(font_bold);
        ui->use_label->setPalette(palette);
        ui->use_label->setStyleSheet(QString("QLabel { background-color : %1; color : white}").arg(app_color::grey_blue));
        ui->use_label->setMinimumSize(0,heigth_label);
        ui->use_label->setIndent(indent_title);
        ui->use_label->show();
        QVector<c_effect> vect_effect = _item.getUseEffects();
        for (QVector<c_effect>::iterator it = vect_effect.begin(); it != vect_effect.end(); ++it) {
            label = new QLabel;
            label->setFont(font);
            label->setPalette(palette);
            label->setIndent(indent_effect);
            label->setMinimumSize(0,heigth_label);
            label->setWordWrap(true);
            QString text_label;
            QString description = replace_image(it->getEffectString(_item.getLvl()).value("text"));
            if (description.isEmpty()) {
                label->setText(replace_image(it->getDescription()));
            } else {
                text_label = QString("%1").arg(replace_image(it->getEffectString(_item.getLvl()).value("text")));
                label->setText(text_label);
                if (text_label.toInt()) {
                    QMap<QString,QString> map = it->interpretState(text_label.toInt());
                    text_label = map.value("text");
                    label->setText(text_label);
                    label->setToolTip(map.value("description"));
                }
            }
            ui->use_layout->addWidget(label);
            label_use_list.push_back(label);
        }
    } else {
        ui->use_label->hide();
    }

    if (_item.getEquipEffects().size()) {
        ui->equip_label->setText(QString("A l'équipement :"));
        ui->equip_label->setFont(font_bold);
        ui->equip_label->setPalette(palette);
        ui->equip_label->setStyleSheet(QString("QLabel#equip_label { background-color : %1; color : white}").arg(color_foreground));
        ui->equip_label->setMinimumSize(0,heigth_label);
        ui->equip_label->setIndent(indent_title);
        ui->equip_label->show();
        QVector<c_effect> vect_effect = _item.getEquipEffects();
        for (QVector<c_effect>::iterator it = vect_effect.begin(); it != vect_effect.end(); ++it) {
            label = new QLabel;
            label->setFont(font);
            label->setPalette(palette);
            label->setWordWrap(true);
            label->setIndent(indent_effect);
            label->setMinimumSize(0,heigth_label);
            QString text_label;
            QString description = replace_image(it->getEffectString(_item.getLvl()).value("text"));
            if (description.isEmpty()) {
                text_label = replace_image(it->getDescription());
            } else {
                text_label= QString("%1").arg(description);
                label->setText(text_label);
            }
            if (text_label.toInt()) {
                QMap<QString,QString> map = it->interpretState(text_label.toInt());
                text_label = map.value("text");
                label->setText(text_label);
                label->setToolTip(map.value("description"));
                qDebug() << text_label << map.value("description");
            }
            if (label_equip_list.size()%2) {
                label->setStyleSheet(QString("QLabel { background-color : %1}").arg(color_foreground));
            }
            if (!description.isEmpty()) {
                ui->equip_layout->addWidget(label);
                label_equip_list.push_back(label);
            }
        }
    }
}

c_item c_item_display::getItem() {
    return _item;
}
