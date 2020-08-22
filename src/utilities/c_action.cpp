#include "c_action.h"

c_action::c_action(int id, QString effect, QString description) : _id(id), _effect(effect), _description(description){}

c_action::c_action(QJsonObject actionObject) {
    _description = actionObject.value(QString("description")).toObject().value(QString("fr")).toString();
    _id = actionObject.value(QString("definition")).toObject().value(QString("id")).toInt();
    _effect = actionObject.value(QString("definition")).toObject().value(QString("effect")).toString();
}

void c_action::setId(const int id) {
    _id = id;
}

void c_action::setEffect(const QString effect) {
    _effect = effect;
}

void c_action::setDescription(const QString description) {
    _description = description;
}

int c_action::getId() const {
    return _id;
}

QString c_action::getEffect() const {
    return _effect;
}

QString c_action::getDescription() const {
    return _description;
}

QString c_action::getText(const QList<float> params,const int lvl) const {
    return tokenizer.formatString(_description,params,lvl,_description.size());
}
