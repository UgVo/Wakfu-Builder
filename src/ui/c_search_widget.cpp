#include "c_search_widget.h"
#include "ui_c_search_widget.h"

c_search_widget::c_search_widget(c_dbmanager *manager, QCompleter* search_completer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_search_widget) {
    ui->setupUi(this);
    dbmanager = manager;
    lvl = 100;
    paliers = QStringList({"0-20","21-35","36-50","51-65","66-80","81-95","96-110","111-125",
               "126-140","141-155","156-170","171-185","186-200","201-215"});
    final = false;
    ui->final_object_check->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/unchecked.png);}"
                                          "QCheckBox::indicator:checked {image: url(:/images/divers/checked.png);}");
    ui->double_slide_bar->setSource(QUrl(QStringLiteral("qrc:/qml/qck_double_slider.qml")));
    slider = ui->double_slide_bar->rootObject();
    QObject::connect(slider, SIGNAL(first_moved(qreal)),
                         this, SLOT(slot_slider_first_moved(qreal)));
    QObject::connect(slider, SIGNAL(second_moved(qreal)),
                         this, SLOT(slot_slider_second_moved(qreal)));
    QObject::connect(ui->lvl_low, SIGNAL(valueChanged(int)),
                         this, SLOT(slot_lvl_low_changed(int)));
    QObject::connect(ui->lvl_high, SIGNAL(valueChanged(int)),
                         this, SLOT(slot_lvl_high_changed(int)));
    QObject::connect(ui->niveau_preDef,&QComboBox::currentTextChanged,this,&c_search_widget::slot_niveau_preDef_changed);

    block = false;
    ui->lvl_high->setValue(150);
    ui->lvl_low->setValue(100);
    ui->niveau_preDef->addItems(paliers);
    init_comboBox(ui->niveau_preDef);
    setLvl(lvl);
    ui->pb_relique->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/relique_low.png);} QCheckBox {color : grey;}"
                                  "QCheckBox::indicator:checked {image: url(:/images/divers/relique_high.png);}");
    QObject::connect(ui->pb_relique,&QCheckBox::stateChanged,this,&c_search_widget::slot_rarity_change_state);
    ui->pb_epique->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/epique_low.png);} QCheckBox {color : grey;}"
                                  "QCheckBox::indicator:checked {image: url(:/images/divers/epique_high.png);}");
    QObject::connect(ui->pb_epique,&QCheckBox::stateChanged,this,&c_search_widget::slot_rarity_change_state);
    ui->pb_legend->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/legendaire_low.png);} QCheckBox {color : grey;}"
                                  "QCheckBox::indicator:checked {image: url(:/images/divers/legendaire_high.png);} ");
    QObject::connect(ui->pb_legend,&QCheckBox::stateChanged,this,&c_search_widget::slot_rarity_change_state);
    ui->pb_mythique->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/mythique_low.png);} QCheckBox {color : grey;}"
                                  "QCheckBox::indicator:checked {image: url(:/images/divers/mythique_high.png);} ");
    QObject::connect(ui->pb_mythique,&QCheckBox::stateChanged,this,&c_search_widget::slot_rarity_change_state);
    ui->pb_souvenir->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/souvenir_low.png);} QCheckBox {color : grey;}"
                                  "QCheckBox::indicator:checked {image: url(:/images/divers/souvenir_high.png);} ");
    QObject::connect(ui->pb_souvenir,&QCheckBox::stateChanged,this,&c_search_widget::slot_rarity_change_state);
    setStyleSheet(QString("c_search_widget {background-color: %1; border: 1px solid %1; border-radius: 4px;}  .QWidget.QWidget{background-color: %2; border: 1px solid %2; border-radius: 4px;} .QSpinBox{background-color: %2; color:white; } .QLabel{color:white} .QGroupeBox{color : white}").arg(app_color::grey_blue).arg(app_color::dark_blue));

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->main_search);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->main_search->setGraphicsEffect(shadow);
    shadow = new QGraphicsDropShadowEffect(ui->advance_search);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->advance_search->setGraphicsEffect(shadow);
    ui->cb_pet->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallpet_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallpet.png);} ");
    ui->cb_back->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallback_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallback.png);} ");
    ui->cb_belt->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallbelt_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallbelt.png);} ");
    ui->cb_head->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallhead_inked.png);}"
                               "QCheckBox::indicator:checked {image: url(:/images/divers/smallhead.png);} ");
    ui->cb_legs->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smalllegs_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smalllegs.png);} ");
    ui->cb_neck->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallneck_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallneck.png);} ");
    ui->cb_ring->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallring_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallring.png);} ");
    ui->cb_chest->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallchest_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallchest.png);} ");
    ui->cb_2_hands->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smalldoublehand_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smalldoublehand.png);} ");
    ui->cb_accessory->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallaccessory_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallaccessory.png);} ");
    ui->cb_shoulders->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallshoulders_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallshoulders.png);} ");
    ui->cb_first_hand->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallfirsthand_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallfirsthand.png);} ");
    ui->cb_second_hand->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallsecondhand_inked.png);}"
                              "QCheckBox::indicator:checked {image: url(:/images/divers/smallsecondhand.png);} ");
    ui->cb_mount->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/smallmount_inked.png);}"
                                "QCheckBox::indicator:checked {image: url(:/images/divers/smallmount.png);} ");

    ui->name_search->setPlaceholderText("Recherche par nom");
    ui->name_search->setStyleSheet(QString(" QLineEdit{background-color: %1;  border: 1px solid %1; color: white;   border-radius: 3px;}"
                                           "name_search::placeholder {color : white;} ").arg(app_color::grey_blue));

    set_comboBox_model(ui->carac_search);

    QObject::connect(ui->search_button,&QPushButton::clicked,this,&c_search_widget::slot_search);
    QObject::connect(ui->reset_button,&QPushButton::clicked,this,&c_search_widget::slot_reset);

    ui->best_combi_gb->setStyleSheet("QGroupBox{color: white;}");

    ui->tri_best_combi_check->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/divers/unchecked.png);}"
                                            "QCheckBox::indicator:checked {image: url(:/images/divers/checked.png);}"
                                            "QCheckBox {color : white;}");

    QObject::connect(ui->best_combi_search,&QPushButton::clicked,this,&c_search_widget::slot_combi_search);
    //QObject::connect(ui->pb_add_condition)

    set_comboBox_model(ui->cb_first_carac);
    static_cast<QStandardItemModel *>(ui->cb_first_carac->model())->item(0,0)->setText("Caractéristique Principale");
    init_comboBox(ui->cb_first_carac);

    cb_carac_list.push_back(ui->cb_carac_1);
    set_comboBox_model(ui->cb_carac_1);
    static_cast<QStandardItemModel *>(ui->cb_carac_1->model())->item(0,0)->setText("Caractéristique secondaire");
    init_comboBox(ui->cb_carac_1);
    cb_carac_list.push_back(ui->cb_carac_2);
    set_comboBox_model(ui->cb_carac_2);
    static_cast<QStandardItemModel *>(ui->cb_carac_2->model())->item(0,0)->setText("Caractéristique secondaire");
    init_comboBox(ui->cb_carac_2);
    cb_carac_list.push_back(ui->cb_carac_3);
    set_comboBox_model(ui->cb_carac_3);
    static_cast<QStandardItemModel *>(ui->cb_carac_3->model())->item(0,0)->setText("Caractéristique secondaire");
    init_comboBox(ui->cb_carac_3);
    cb_carac_list.push_back(ui->cb_carac_4);
    set_comboBox_model(ui->cb_carac_4);
    static_cast<QStandardItemModel *>(ui->cb_carac_4->model())->item(0,0)->setText("Caractéristique secondaire");
    init_comboBox(ui->cb_carac_4);
    cb_carac_list.push_back(ui->cb_carac_5);
    set_comboBox_model(ui->cb_carac_5);
    static_cast<QStandardItemModel *>(ui->cb_carac_5->model())->item(0,0)->setText("Caractéristique secondaire");
    init_comboBox(ui->cb_carac_5);
    cb_carac_list.push_back(ui->cb_carac_6);
    set_comboBox_model(ui->cb_carac_6);
    static_cast<QStandardItemModel *>(ui->cb_carac_6->model())->item(0,0)->setText("Caractéristique secondaire");
    init_comboBox(ui->cb_carac_6);

    cb_carac_condi.push_back(ui->cb_condi_1);
    init_comboBox(ui->cb_condi_1);
    cb_carac_condi.push_back(ui->cb_condi_2);
    init_comboBox(ui->cb_condi_2);
    cb_carac_condi.push_back(ui->cb_condi_3);
    init_comboBox(ui->cb_condi_3);
    cb_carac_condi.push_back(ui->cb_condi_4);
    init_comboBox(ui->cb_condi_4);
    cb_carac_condi.push_back(ui->cb_condi_5);
    init_comboBox(ui->cb_condi_5);
    cb_carac_condi.push_back(ui->cb_condi_6);
    init_comboBox(ui->cb_condi_6);

    numberShown = 2;

    for (int i = numberShown; i < cb_carac_list.size(); ++i) {
        cb_carac_list[i]->hide();
        cb_carac_condi[i]->hide();
    }

    QObject::connect(ui->pb_add_condition,&QPushButton::clicked,this,&c_search_widget::slot_new_condi_row);

    completer = search_completer;
    ui->name_search->setCompleter(completer);

}

c_search_widget::~c_search_widget() {
    delete ui;
}

void c_search_widget::slot_slider_first_moved(qreal val) {
    block = !block;
    if (!block) {
        return;
    }
    int value = qFloor(val);
    ui->lvl_low->setValue(value);
}

void c_search_widget::slot_slider_second_moved(qreal val) {
    block = !block;
    if (!block) {
        return;
    }
    int value = qFloor(val);
    ui->lvl_high->setValue(value);
}

void c_search_widget::slot_lvl_low_changed(int val) {
    block = !block;
    if (!block) {
        return;
    }
    QMetaObject::invokeMethod(slider, "setFirst",Q_ARG(QVariant, QVariant(val)));
    ui->double_slide_bar->update();

}

void c_search_widget::slot_lvl_high_changed(int val) {
    block = !block;
    if (!block) {
        return;
    }
    QMetaObject::invokeMethod(slider, "setSecond",Q_ARG(QVariant, QVariant(val)));
    ui->double_slide_bar->update();
}

void c_search_widget::slot_niveau_preDef_changed(const QString& string) {
    QStringList values = string.split("-");
    int second = values.at(1).toInt();
    int first = values.at(0).toInt();
    if(second < ui->lvl_low->value()) {
        ui->lvl_low->setValue(first);
        ui->lvl_high->setValue(second);
    } else {
        ui->lvl_high->setValue(second);
        ui->lvl_low->setValue(first);
    }
}

void c_search_widget::setLvl(int new_lvl) {
    foreach (QString string,paliers) {
        QStringList values = string.split("-");
        if (values.at(1).toInt()>=new_lvl && values.at(0).toInt() <= new_lvl) {
            ui->niveau_preDef->setCurrentText(string);
            lvl = new_lvl;
            return;
        }
    }
}

void c_search_widget::slot_load_search_position(QString position) {

    ui->cb_back->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_pet->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_belt->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_2_hands->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_ring->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_first_hand->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_second_hand->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_legs->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_neck->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_head->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_chest->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_shoulders->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_accessory->setCheckState(Qt::CheckState::Unchecked);

    if (!position.compare(c_item::FIRST_WEAPON)) {
        ui->cb_first_hand->setCheckState(Qt::CheckState::Checked);
        ui->cb_2_hands->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::SECOND_WEAPON)) {
        ui->cb_second_hand->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::LEFT_HAND) || !position.compare(c_item::RIGHT_HAND)) {
        ui->cb_ring->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::LEGS)) {
        ui->cb_legs->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::NECK)) {
        ui->cb_neck->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::BACK)) {
        ui->cb_back->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::BELT)) {
        ui->cb_belt->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::HEAD)) {
        ui->cb_head->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::CHEST)) {
        ui->cb_chest->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::SHOULDERS)) {
        ui->cb_shoulders->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::ACCESSORY)) {
        ui->cb_accessory->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::PET)) {
        ui->cb_pet->setCheckState(Qt::CheckState::Checked);
    } else if (!position.compare(c_item::MOUNT)) {
        ui->cb_mount->setCheckState(Qt::CheckState::Checked);
    }
    QList<int> itemType;
    QStringList map = c_item::mapPositionToType.values(position);
    foreach(QString position_elem, map) {
        itemType.append(c_item::mapTypeToId.values(position_elem));
    }

    if (ui->cb_2_hands->isChecked()) itemType.append(c_item::mapTypeToId.values("TWO_HAND_WEAPON"));

    QList<int> rarities;
    if (ui->pb_epique->isChecked()) rarities.append(c_item::mapRarityToId["Epique"]);
    if (ui->pb_legend->isChecked()) rarities.append(c_item::mapRarityToId["Légendaire"]);
    if (ui->pb_mythique->isChecked()) rarities.append(c_item::mapRarityToId["Mythique"]);
    if (ui->pb_relique->isChecked()) rarities.append(c_item::mapRarityToId["Relique"]);
    if (ui->pb_souvenir->isChecked()) rarities.append(c_item::mapRarityToId["Souvenir"]);

    QList<QString> caract;
    if (ui->carac_search->currentIndex()!=0) caract.append(ui->carac_search->currentText());
    QList<int> item_list = dbmanager->getid_item_from_actions(caract,rarities,itemType, {ui->lvl_low->value(),ui->lvl_high->value()},ui->name_search->text(),ui->final_object_check->checkState()==Qt::CheckState::Checked);
    emit new_search_result(item_list);
}

void c_search_widget::slot_rarity_change_state(bool checked) {
     QCheckBox* sender = static_cast<QCheckBox*>(QObject::sender());

     QString name = sender->text().replace(QRegExp("[éèëê]"),"e").toLower();
     if (checked) {
         sender->setStyleSheet( QString("QCheckBox::indicator:unchecked {image: url(:/images/divers/%1_low.png);}"
                                "QCheckBox::indicator:checked {image: url(:/images/divers/%1_high.png);} QCheckBox {color : white;}").arg(name));
     } else {
         sender->setStyleSheet( QString("QCheckBox::indicator:unchecked {image: url(:/images/divers/%1_low.png);}"
                                "QCheckBox::indicator:checked {image: url(:/images/divers/%1_high.png);} QCheckBox {color : grey;}").arg(name));
     }
}

void c_search_widget::slot_search() {
    QList<int> itemType;
    if (ui->cb_back->isChecked()) itemType.append(c_item::mapTypeToId["BACK"]);
    if (ui->cb_pet->isChecked()) itemType.append(c_item::mapTypeToId["PET"]);
    if (ui->cb_belt->isChecked()) itemType.append(c_item::mapTypeToId["BELT"]);
    if (ui->cb_2_hands->isChecked()) itemType.append(c_item::mapTypeToId.values("TWO_HAND_WEAPON"));
    if (ui->cb_ring->isChecked()) itemType.append(c_item::mapTypeToId["RING"]);
    if (ui->cb_first_hand->isChecked()) itemType.append(c_item::mapTypeToId.values("ONE_HAND_WEAPON"));
    if (ui->cb_second_hand->isChecked()) itemType.append(c_item::mapTypeToId.values("SECOND_HAND"));
    if (ui->cb_legs->isChecked()) itemType.append(c_item::mapTypeToId["LEGS"]);
    if (ui->cb_neck->isChecked()) itemType.append(c_item::mapTypeToId["NECK"]);
    if (ui->cb_head->isChecked()) itemType.append(c_item::mapTypeToId["HEAD"]);
    if (ui->cb_chest->isChecked()) itemType.append(c_item::mapTypeToId["CHEST"]);
    if (ui->cb_shoulders->isChecked()) itemType.append(c_item::mapTypeToId["SHOULDERS"]);
    if (ui->cb_accessory->isChecked()) itemType.append(c_item::mapTypeToId.values("ACCESSORY"));
    if (ui->cb_mount->isChecked()) itemType.append(c_item::mapTypeToId["MOUNT"]);

    QList<int> rarities;
    if (ui->pb_epique->isChecked()) rarities.append(c_item::mapRarityToId["Epique"]);
    if (ui->pb_legend->isChecked()) rarities.append(c_item::mapRarityToId["Légendaire"]);
    if (ui->pb_mythique->isChecked()) rarities.append(c_item::mapRarityToId["Mythique"]);
    if (ui->pb_relique->isChecked()) rarities.append(c_item::mapRarityToId["Relique"]);
    if (ui->pb_souvenir->isChecked()) rarities.append(c_item::mapRarityToId["Souvenir"]);

    QList<QString> caract;
    if (ui->carac_search->currentIndex()!=0) caract.append(ui->carac_search->currentText());
    QList<int> item_list = dbmanager->getid_item_from_actions(caract,rarities,itemType, {ui->lvl_low->value(),ui->lvl_high->value()},ui->name_search->text(),ui->final_object_check->isChecked());
    emit new_search_result(item_list);

}

bool c_search_widget::compare_pair_id_lvl(QPair<int,int> p1, QPair<int,int> p2) {
    return p1.second < p2.second;
}

void c_search_widget::init_comboBox(QComboBox* cb) {
    cb->setStyleSheet(QString("QComboBox { background-color: %1;  border: 1px solid %1; color:white;   border-radius: 3px;} QComboBox::drop-down { width: 16px;    border: %1 solid %1; border-bottom-right-radius: 3px;} QComboBox::down-arrow {image: url(:/images/divers/down_arrow.png);} QComboBox::down-arrow:on {image: url(:/images/divers/up_arrow.png);} QComboBox::item{ border: 0px solid black } ").arg(app_color::grey_blue));
    cb->view()->setStyleSheet(QString("QAbstractItemView {background-color : %1; selection-background-color: %2; outline: 0px; border: 1px solid %1; border-radius: 3px;}").arg(app_color::grey_blue).arg(app_color::green_blue));
    for (int i = 0; i < cb->count(); ++i) {
       cb->setItemData(i, QBrush(QColor("white")), Qt::TextColorRole);
    }
}

void c_search_widget::slot_reset() {
    ui->carac_search->setCurrentIndex(0);
    ui->cb_back->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_pet->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_belt->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_2_hands->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_ring->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_first_hand->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_second_hand->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_legs->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_neck->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_head->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_chest->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_shoulders->setCheckState(Qt::CheckState::Unchecked);
    ui->cb_accessory->setCheckState(Qt::CheckState::Unchecked);
    ui->pb_epique->setCheckState(Qt::CheckState::Unchecked);
    ui->pb_legend->setCheckState(Qt::CheckState::Unchecked);
    ui->pb_mythique->setCheckState(Qt::CheckState::Unchecked);
    ui->pb_relique->setCheckState(Qt::CheckState::Unchecked);
    ui->pb_souvenir->setCheckState(Qt::CheckState::Unchecked);
    ui->name_search->setText("");
}

void c_search_widget::slot_combi_search() {
    QList<int> itemType;
    if (ui->cb_back->isChecked()) itemType.append(c_item::mapTypeToId["BACK"]);
    if (ui->cb_pet->isChecked()) itemType.append(c_item::mapTypeToId["PET"]);
    if (ui->cb_belt->isChecked()) itemType.append(c_item::mapTypeToId["BELT"]);
    if (ui->cb_2_hands->isChecked()) itemType.append(c_item::mapTypeToId.values("TWO_HAND_WEAPON"));
    if (ui->cb_ring->isChecked()) itemType.append(c_item::mapTypeToId["RING"]);
    if (ui->cb_first_hand->isChecked()) itemType.append(c_item::mapTypeToId.values("ONE_HAND_WEAPON"));
    if (ui->cb_second_hand->isChecked()) itemType.append(c_item::mapTypeToId.values("SECOND_HAND"));
    if (ui->cb_legs->isChecked()) itemType.append(c_item::mapTypeToId["LEGS"]);
    if (ui->cb_neck->isChecked()) itemType.append(c_item::mapTypeToId["NECK"]);
    if (ui->cb_head->isChecked()) itemType.append(c_item::mapTypeToId["HEAD"]);
    if (ui->cb_chest->isChecked()) itemType.append(c_item::mapTypeToId["CHEST"]);
    if (ui->cb_shoulders->isChecked()) itemType.append(c_item::mapTypeToId["SHOULDERS"]);
    if (ui->cb_accessory->isChecked()) itemType.append(c_item::mapTypeToId.values("ACCESSORY"));
    if (ui->cb_mount->isChecked()) itemType.append(c_item::mapTypeToId["MOUNT"]);

    QList<int> rarities;
    if (ui->pb_epique->isChecked()) rarities.append(c_item::mapRarityToId["Epique"]);
    if (ui->pb_legend->isChecked()) rarities.append(c_item::mapRarityToId["Légendaire"]);
    if (ui->pb_mythique->isChecked()) rarities.append(c_item::mapRarityToId["Mythique"]);
    if (ui->pb_relique->isChecked()) rarities.append(c_item::mapRarityToId["Relique"]);
    if (ui->pb_souvenir->isChecked()) rarities.append(c_item::mapRarityToId["Souvenir"]);

    QList<bool> caract_condi;
    QList<QString> caract_name;

    if (ui->cb_first_carac->currentIndex()!=0) caract_name.append(ui->cb_first_carac->currentText());
    for (int i = 0; i < numberShown; ++i) {
        if (cb_carac_list.at(i)->currentIndex()) {
            caract_condi.append(cb_carac_condi.at(i)->currentText() == "Ou");
            caract_name.append(cb_carac_list.at(i)->currentText());
        }
    }
    slot_reset_combi();
    numberShown  = caract_condi.size();
    for (int i = 0; i < numberShown; ++i) {
        cb_carac_list.at(i)->setCurrentText(caract_name.at(i+1));
        cb_carac_condi.at(i)->setCurrentIndex(caract_condi.at(i));
    }

    for (int i = numberShown; i < cb_carac_list.size(); ++i) {
        cb_carac_list.at(i)->hide();
        cb_carac_condi.at(i)->hide();
    }
    if (ui->tri_best_combi_check->isChecked()) {
        QList<int> item_list = dbmanager->getid_item_from_actions_sorted(caract_name,rarities,itemType, {ui->lvl_low->value(),ui->lvl_high->value()},ui->name_search->text(),ui->final_object_check->isChecked(),caract_condi.mid(0,caract_name.size()-1));
        emit new_search_result_sorted(item_list);
    } else {
        QList<int> item_list = dbmanager->getid_item_from_actions(caract_name,rarities,itemType, {ui->lvl_low->value(),ui->lvl_high->value()},ui->name_search->text(),ui->final_object_check->isChecked(),caract_condi);
        emit new_search_result(item_list);
    }
}

void c_search_widget::slot_reset_combi() {
    for (int i = 0; i < cb_carac_list.size(); ++i) {
        cb_carac_list.at(i)->setCurrentIndex(0);
        cb_carac_condi.at(i)->setCurrentIndex(0);
    }
}

void c_search_widget::slot_new_condi_row() {
    if (numberShown < cb_carac_list.size()) {
        cb_carac_list.at(numberShown)->show();
        cb_carac_condi.at(numberShown)->show();
        numberShown++;
    }
}

void c_search_widget::set_comboBox_model(QComboBox *cb) {

#if defined(Q_OS_MAC)
    cb->setStyle(QStyleFactory::create("Windows"));
#endif

    cb->addItem("Recherche par caractéristique");
    cb->addItem("Principales");
    cb->addItem(QIcon(":/images/Aptitudes/vie.png"),"Vie");
    cb->addItem(QIcon(":/images/Aptitudes/pa.png"),"PA");
    cb->addItem(QIcon(":/images/Aptitudes/pm.png"),"PM");
    cb->addItem(QIcon(":/images/Aptitudes/wakfu.png"),"PW");
    cb->addItem("Secondaires");
    cb->addItem(QIcon(":/images/Aptitudes/resi.png"),"Parade");
    cb->addItem(QIcon(":/images/Aptitudes/critique.png"),"Coup Critique");
    cb->addItem(QIcon(":/images/Aptitudes/init.png"),"Initiative");
    cb->addItem(QIcon(":/images/Aptitudes/porte.png"),"Portée");
    cb->addItem(QIcon(":/images/Aptitudes/esquive.png"),"Esquive");
    cb->addItem(QIcon(":/images/Aptitudes/tacle.png"),"Tacle");
    cb->addItem(QIcon(":/images/Aptitudes/sagesse.png"),"Sagesse");
    cb->addItem(QIcon(":/images/Aptitudes/prospection.png"),"Prospection");
    cb->addItem(QIcon(":/images/Aptitudes/controle.png"),"Contrôle");
    cb->addItem(QIcon(":/images/Aptitudes/barda.png"),"Art du barda");
    cb->addItem(QIcon(":/images/Aptitudes/volonte.png"),"Volonté");
    cb->addItem("Maitrises");
    cb->addItem(QIcon(":/images/Aptitudes/dommages.png"),"Maîtrise Élémentaire");
    cb->addItem(QIcon(":/images/elements/FIRE.png"),"Maîtrise Élémentaire Feu");
    cb->addItem(QIcon(":/images/elements/WATER.png"),"Maîtrise Élémentaire Eau");
    cb->addItem(QIcon(":/images/elements/EARTH.png"),"Maîtrise Élémentaire Terre");
    cb->addItem(QIcon(":/images/elements/WIND.png"),"Maîtrise Élémentaire Air");
    cb->addItem(QIcon(":/images/Aptitudes/dommages.png"),"Maîtrise sur 1 éléments");
    cb->addItem(QIcon(":/images/Aptitudes/dommages.png"),"Maîtrise sur 2 éléments");
    cb->addItem(QIcon(":/images/Aptitudes/dommages.png"),"Maîtrise sur 3 éléments");
    cb->addItem(QIcon(":/images/Aptitudes/maitrise_critique.png"),"Maîtrise Critique");
    cb->addItem(QIcon(":/images/Aptitudes/maitrise_dos.png"),"Maîtrise Dos");
    cb->addItem(QIcon(":/images/Aptitudes/distance.png"),"Maîtrise Distance");
    cb->addItem(QIcon(":/images/Aptitudes/melee.png"),"Maîtrise Mêlée");
    cb->addItem(QIcon(":/images/Aptitudes/mono.png"),"Maîtrise Monocible");
    cb->addItem(QIcon(":/images/Aptitudes/zone.png"),"Maîtrise Zone");
    cb->addItem(QIcon(":/images/Aptitudes/soin.png"),"Maîtrise Soin");
    cb->addItem(QIcon(":/images/Aptitudes/berserk.png"),"Maîtrise Berserk");
    cb->addItem(QIcon(":/images/Aptitudes/armor_given.png"),"Armure donnée");
    cb->addItem(QIcon(":/images/Aptitudes/armor_gotten.png"),"Armure reçue");
    cb->addItem("Résistances");
    cb->addItem(QIcon(":/images/Aptitudes/resi.png"),"Résistance Élémentaire");
    cb->addItem(QIcon(":/images/Aptitudes/resi.png"),"Résistance sur 1 éléments");
    cb->addItem(QIcon(":/images/Aptitudes/resi.png"),"Résistance sur 2 éléments");
    cb->addItem(QIcon(":/images/Aptitudes/resi.png"),"Résistance sur 3 éléments");
    cb->addItem(QIcon(":/images/Aptitudes/resistance_critique.png"),"Résistance Critique");
    cb->addItem(QIcon(":/images/Aptitudes/resistance_dos.png"),"Résistance Dos");

    cb->addItem("Niveaux de sort");
    cb->addItem(QIcon(":/images/elements/FIRE.png"),"Niv. aux sorts Feu");
    cb->addItem(QIcon(":/images/elements/WATER.png"),"Niv. aux sorts Eau");
    cb->addItem(QIcon(":/images/elements/EARTH.png"),"Niv. aux sorts Terre");
    cb->addItem(QIcon(":/images/elements/WIND.png"),"Niv. aux sorts Air");
    cb->setCurrentIndex(0);

    init_comboBox(cb);

    QFont font = static_cast<QStandardItemModel *>(cb->model())->item(1,0)->font();
    font.setPointSize(9);
    font.setBold(true);
    static_cast<QStandardItemModel *>(cb->model())->item(1,0)->setFont(font);
    static_cast<QStandardItemModel *>(cb->model())->item(1,0)->setEnabled(false);
    static_cast<QStandardItemModel *>(cb->model())->item(6,0)->setFont(font);
    static_cast<QStandardItemModel *>(cb->model())->item(6,0)->setEnabled(false);
    static_cast<QStandardItemModel *>(cb->model())->item(18,0)->setFont(font);
    static_cast<QStandardItemModel *>(cb->model())->item(18,0)->setEnabled(false);
    static_cast<QStandardItemModel *>(cb->model())->item(37,0)->setFont(font);
    static_cast<QStandardItemModel *>(cb->model())->item(37,0)->setEnabled(false);
    static_cast<QStandardItemModel *>(cb->model())->item(44,0)->setFont(font);
    static_cast<QStandardItemModel *>(cb->model())->item(44,0)->setEnabled(false);
}
