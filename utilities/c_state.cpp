#include "c_state.h"

c_state::c_state(int id, QString name, QString description) {
    _id = id;
    _name = name;
    _description = description;
}

c_state::c_state(QJsonObject state) {
    _id = state.value("definition").toObject().value("id").toInt();
    _name = state.value("title").toObject().value("fr").toString();
    _description = state.value("description").toObject().value("fr").toString();
}

int c_state::get_id() {
    return _id;
}

QString c_state::get_name() {
    return _name;
}

QString c_state::get_description() {
    return _description;
}

void c_state::set_id(int id) {
    _id = id;
}

void c_state::set_name(QString name) {
    _name = name;
}

void c_state::set_description(QString description) {
    _description = description;
}
