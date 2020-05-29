#include "c_io_manager.h"
#include "ui/c_builder_view.h"

c_io_manager::c_io_manager(c_dbmanager *_db_manager, QObject *parent) : QObject(parent) {
    db_manager = _db_manager;
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

QByteArray c_io_manager::save(const c_builder_view *builder, const c_io_manager::jsonformat format, const QString path) {
    QJsonDocument doc;
    doc.setObject(builderToJson(builder));

    if (format == c_io_manager::jsonformat::file) {
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    } else if (format ==  c_io_manager::jsonformat::database) {
        // TODO insert to database
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


void c_io_manager::load(c_builder_view *builder, const c_io_manager::jsonformat format, QString path, int id) {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonArray JsonArray;

    if (format == c_io_manager::jsonformat::file) {
        file.setFileName(path);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        doc = QJsonDocument::fromJson(val.toUtf8());
        jsonToBuilder(builder,doc.object());
    }
}
