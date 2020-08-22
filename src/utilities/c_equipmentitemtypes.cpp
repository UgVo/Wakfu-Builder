#include "c_equipmentitemtypes.h"

c_equipmentItemTypes::c_equipmentItemTypes(int _id, int _parentId, QStringList _equipementPositions,
                                           QStringList _equipementDisablePositions, bool _recyclable, bool _visibleInAnimation,
                                           QString _title) {
    id = _id;
    parentId = _parentId;
    equipementPositions = _equipementPositions;
    equipmentDisabledPositions = _equipementDisablePositions;
    recyclable = _recyclable;
    visibleInAnimation = _visibleInAnimation;
    title = _title;
}

c_equipmentItemTypes::c_equipmentItemTypes(QJsonObject object) {
    id = int(object.value(QString("definition")).toObject().value(QString("id")).toInt());
    parentId = int(object.value(QString("definition")).toObject().value(QString("parentId")).toInt());
    recyclable = object.value(QString("definition")).toObject().value(QString("isRecyclable")).toBool();
    visibleInAnimation = object.value(QString("definition")).toObject().value(QString("isVisibleInAnimation")).toBool();
    title = object.value(QString("title")).toObject().value(QString("fr")).toString();
    QJsonArray array = object.value(QString("definition")).toObject().value(QString("equipmentPositions")).toArray();
    for (int i = 0; i < array.size(); ++i) {
        equipementPositions.push_back(array.at(i).toString());
    }
    array = object.value(QString("definition")).toObject().value(QString("equipmentDisabledPositions")).toArray();
    for (int i = 0; i < array.size(); ++i) {
        equipmentDisabledPositions.push_back(array.at(i).toString());
    }
}

int c_equipmentItemTypes::getId() const {
    return id;
}

int c_equipmentItemTypes::getParentId() const {
    return parentId;
}

QStringList c_equipmentItemTypes::getEquipementPositions() const {
    return equipementPositions;
}

QStringList c_equipmentItemTypes::getEquipementDisablePositions() const {
    return equipmentDisabledPositions;
}

bool c_equipmentItemTypes::isRecyclable() const {
    return recyclable;
}

bool c_equipmentItemTypes::isVisibleInAnimation() const {
    return visibleInAnimation;
}

QString c_equipmentItemTypes::getTitle() const {
    return  title;
}

void c_equipmentItemTypes::setId(const int _id) {
    id = _id;
}

void c_equipmentItemTypes::setParentId(const int _parentId) {
    parentId = _parentId;
}

void c_equipmentItemTypes::setEquipementPositions(const QStringList _equipementPositions) {
    equipementPositions = _equipementPositions;
}

void c_equipmentItemTypes::setEquipementDisablePositions(const QStringList _equipementDisablePositions) {
    equipmentDisabledPositions = _equipementDisablePositions;
}

void c_equipmentItemTypes::setRecyclable(const bool _recyclable) {
    recyclable = _recyclable;
}

void c_equipmentItemTypes::setVisibleInAnimation(const bool _visibleInAnimation) {
    visibleInAnimation = _visibleInAnimation;
}

void c_equipmentItemTypes::setTitle(const QString _title) {
    title = _title;
}
