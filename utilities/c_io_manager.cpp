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
    QMap<QString, c_item> map_item = build->getEquipment();
    foreach(QString key, map_item.keys()) {
        array_item[key] = itemToJson(map_item[key]);
    }
    res["equipment"] = array_item;
    res["lvl"] = status->getLvl();
    res["elements"] = QJsonArray::fromStringList(build->getElements());
    res["name"] = status->getName();

    return res;
}

QByteArray c_io_manager::save(c_builder_view *builder, const c_io_manager::jsonformat format, const QString path) {
    QJsonDocument doc;
    doc.setObject(builderToJson(builder));

    if (format == c_io_manager::jsonformat::file) {
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        builder->setId(-1);
    } else if (format ==  c_io_manager::jsonformat::database) {
        if (!builder->getId()) {
            int id = db_manager->add_save_builder(doc.toJson(QJsonDocument::Indented),builder->getStatus_build()->getName(),builder->getStatus_build()->getLvl());
            builder->setId(id);
        } else {
            db_manager->update_save_builder(doc.toJson(QJsonDocument::Indented),builder->getId(),builder->getStatus_build()->getName(),builder->getStatus_build()->getLvl());
        }
    }

    return doc.toJson(QJsonDocument::Compact);
}

void c_io_manager::jsonToBuilder(c_builder_view *builder, const QJsonObject &json) {
    c_status_build *status = builder->getStatus_build();
    c_build_display *build_display = builder->getBuild_display();
    c_build *build = build_display->build();
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
