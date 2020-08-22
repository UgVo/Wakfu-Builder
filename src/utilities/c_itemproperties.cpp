#include "c_itemproperties.h"

c_itemProperties::c_itemProperties(int _id, QString _name, QString _description) {
    id = _id;
    name = _name;
    description = _description;
}

c_itemProperties::c_itemProperties(QJsonObject actionObject) {
    id = int(actionObject.value(QString("id")).toInt());
    name = actionObject.value(QString("name")).toString();
    description = actionObject.value(QString("description")).toString();
}

int c_itemProperties::getId() const {
    return id;
}

QString c_itemProperties::getName() const {
    return name;
}

QString c_itemProperties::getDescription() const {
    return description;
}

void c_itemProperties::setId(const int _id) {
    id = _id;
}

void c_itemProperties::setName(const QString _name) {
    name = _name;
}
void c_itemProperties::setDescription(const QString _description) {
    description = _description;
}
