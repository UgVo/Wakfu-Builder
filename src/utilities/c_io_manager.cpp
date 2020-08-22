#include "c_io_manager.h"
#include "ui/c_builder_view.h"

c_io_manager::c_io_manager(c_dbmanager *_db_manager, QObject *parent) : QObject(parent) {
    db_manager = _db_manager;
    load_builder_dialog = new c_load_builder_dialog(db_manager);
}

QJsonObject c_io_manager::itemToJson(const c_item &item) {
    QJsonObject json;
    json["id"] = item.getId();
    json["elems"] = QJsonArray::fromStringList(item.getElements());

    return json;
}

QJsonObject c_io_manager::builderToJson(const c_builder_view *builder) {
    QJsonObject res;
    QJsonObject array_item;
    c_build *build = builder->getBuild_display()->build();
    c_status_build* status = builder->getStatus_build();
    c_enchantement_display* enchant = builder->getEnchantement_display();
    QMap<QString, c_item> map_item = build->getEquipment();
    foreach(QString key, map_item.keys()) {
        array_item[key] = itemToJson(map_item[key]);
    }
    res["equipment"] = array_item;
    res["lvl"] = status->getLvl();
    res["elements"] = QJsonArray::fromStringList(build->getElements());
    res["name"] = status->getName();
    res["aptitudes"] = aptitudeToJson(build->getBonus_aptitudes());
    res["bonus_hm"] = status->isActivated_HM();
    res["bonus_nation"] = status->isActivated_Nation();
    res["bonus_guilde"] = status->isActivated_Guilde();
    res["classe"] = status->getClasse();
    res["enchant"] = enchantToJson(enchant->getItem_slots_map());

    return res;
}

QJsonObject c_io_manager::aptitudeToJson(const QMap<QString, int> bonuses) {
    QJsonObject array_item;
    foreach(QString key, bonuses.keys()) {
        array_item[key] = bonuses[key];
    }
    return array_item;
}

QJsonObject c_io_manager::enchantToJson(const QMap<QString,c_enchantement_item*> item_sets) {
    QJsonObject array_set;
    foreach (QString key, item_sets.keys()){
        QList<c_enchantement_chasse> list = item_sets[key]->chasse_list();
        QJsonArray array_item;
        for (int j = 0; j < list.size(); ++j) {
            QJsonObject chasse;
            chasse["level"] = list[j].level();
            chasse["effect"] = list[j].effect().effect();
            chasse["color"] = list[j].color();
            chasse["white"] = list[j].white();
            array_item.push_back(chasse);
        }
        array_set[key] = array_item;
    }
    return array_set;
}

QByteArray c_io_manager::save(c_builder_view *builder, const c_io_manager::jsonformat format, const QString path) {
    QJsonDocument doc;
    doc.setObject(builderToJson(builder));

    if (format == c_io_manager::jsonformat::file) {
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.resize(0);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        builder->setId(-1);
    } else if (format ==  c_io_manager::jsonformat::database) {
        if (!builder->getId() || builder->getId()==-1) {
            int id = db_manager->add_save_builder(doc.toJson(QJsonDocument::Indented),builder->getStatus_build()->getName(),builder->getStatus_build()->getLvl());
            builder->setId(id);
        } else {
            if (!db_manager->update_save_builder(doc.toJson(QJsonDocument::Indented),builder->getId(),builder->getStatus_build()->getName(),builder->getStatus_build()->getLvl())) {
                int id = db_manager->add_save_builder(doc.toJson(QJsonDocument::Indented),builder->getStatus_build()->getName(),builder->getStatus_build()->getLvl());
                builder->setId(id);
            }
        }
    }

    return doc.toJson(QJsonDocument::Compact);
}

void c_io_manager::jsonToBuilder(c_builder_view *builder, const QJsonObject &json) {
    c_status_build *status = builder->getStatus_build();
    c_build_display *build_display = builder->getBuild_display();
    c_build *build = build_display->build();
    c_aptitudes_display *apt_display = builder->getAptitude_display();
    c_enchantement_display* enchant = builder->getEnchantement_display();
    status->setLvl(json.value("lvl").toInt());
    foreach(QString key, c_item::position()) {
        int id = json.value("equipment").toObject().value(key).toObject().value("id").toInt();
        c_item item = db_manager->get_item(id);
        QVariantList elems_variant = json.value("equipment").toObject().value(key).toObject().value("elems").toArray().toVariantList();
        QStringList elems;
        foreach(QVariant elem, elems_variant) {
            elems.push_back(elem.toString());
        }
        item.setElements(elems);
        build->equip(item);
    }
    QVariantList elems_variant = json.value("elements").toArray().toVariantList();
    QStringList elems;
    foreach(QVariant elem, elems_variant) {
        elems.push_back(elem.toString());
    }
    c_elements_display *elem_display = builder->getElement_display();
    elem_display->setElements(elems);
    status->setName(json.value("name").toString());

    if (json.contains("aptitudes")) {
        apt_display->slot_set_aptitudes(jsonToAptitudeMap(json.value("aptitudes").toObject()));
    }
    if (json.contains("bonus_hm")) {
        status->Activated_HM(json.value("bonus_hm").toBool());
    }
    if (json.contains("bonus_nation")) {
        status->Activated_Nation(json.value("bonus_nation").toBool());
    }
    if (json.contains("bonus_guilde")) {
        status->Activated_Guilde(json.value("bonus_guilde").toBool());
    }
    if (json.contains("classe")) {
        status->slot_class_changed(json.value("classe").toInt());
    }
    if (json.contains("enchant")) {
        enchant->setChasses(jsonToEnchantMap(json.value("enchant").toObject()));
    }
}

QMap<QString,int> c_io_manager::jsonToAptitudeMap(const QJsonObject &json) {
    QMap<QString,int> map;
    foreach(QString key ,json.keys()) {
        map[key] = json.value(key).toInt();
    }
    return map;
}

QMap<QString, QList<c_enchantement_chasse>> c_io_manager::jsonToEnchantMap(const QJsonObject &json) {
    QMap<QString, QList<c_enchantement_chasse>> map;
    foreach (QString key, json.keys()) {
        QJsonArray array = json.value(key).toArray();
        for (QJsonArray::iterator it = array.begin(); it != array.end(); ++it) {
            c_enchantement_chasse chasse;
            QJsonObject object = it->toObject();
            chasse.setWhite(object.value("white").toBool());
            chasse.setColor(object.value("color").toInt());
            chasse.setChasseLevel(object.value("level").toInt());
            qDebug() << "---- lvl ----" << object.value("level").toInt() << chasse.level();
            chasse.setEffect(db_manager->get_enchantement_effect(object.value("effect").toString()));
            map[key].push_back(chasse);
        }
    }
    return map;
}


bool c_io_manager::load(c_builder_view *builder, const c_io_manager::jsonformat format, QString path, int id) {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonArray JsonArray;

    if (format == c_io_manager::jsonformat::file) {
        bool res;
        file.setFileName(path);
        res = file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        doc = QJsonDocument::fromJson(val.toUtf8());
        jsonToBuilder(builder,doc.object());
        builder->setId(-1);
        builder->setPath(path);
        return res;
    } else if (format == c_io_manager::jsonformat::database) {
        if (QDialog::Accepted == load_builder_dialog->exec()) {
            QString json = load_builder_dialog->getCurrent_json();
            if (json.isEmpty()) {
                return false;
            }
            doc = QJsonDocument::fromJson(json.toUtf8());
            jsonToBuilder(builder,doc.object());
            builder->setId(load_builder_dialog->getCurrent_id());
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool c_io_manager::loadFrom(c_builder_view *builder, const c_io_manager::jsonformat format, QString path_json, int id) {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonArray JsonArray;

    if (format == c_io_manager::jsonformat::file) {
        bool res;
        file.setFileName(path_json);
        res = file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        doc = QJsonDocument::fromJson(val.toUtf8());
        jsonToBuilder(builder,doc.object());
        builder->setId(id);
        builder->setPath(path_json);
        return res;
    } else if (format == c_io_manager::jsonformat::database) {
        doc = QJsonDocument::fromJson(path_json.toUtf8());
        jsonToBuilder(builder,doc.object());
        builder->setId(id);
        return true;
    }
    return false;
}

void c_io_manager::update(c_builder_view *builder, const c_io_manager::jsonformat format, const QString path) {
    QJsonDocument doc;
    doc.setObject(builderToJson(builder));

    if (format == c_io_manager::jsonformat::file) {
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.resize(0);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        builder->setId(-1);
    } else if (format ==  c_io_manager::jsonformat::database) {
        db_manager->update_save_builder(doc.toJson(QJsonDocument::Indented),builder->getId(),builder->getStatus_build()->getName(),builder->getStatus_build()->getLvl());
    }
}
