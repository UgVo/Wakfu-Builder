#include "c_effect.h"
#include <utilities/c_dbmanager.h>

c_effect::c_effect(c_dbmanager *dbmanager, int id, c_action action, int areaShape, QVector<int> areaSize, QVector<float> params, QString description) {
    _id = id;
    _action = action;
    _areaShape = areaShape;
    _areaSize = areaSize;
    _params = params;
    _description = description;
    _database = dbmanager;
}

c_effect::c_effect(QJsonObject object, c_dbmanager *dbmanager) {
    _database = dbmanager;
    QJsonObject definition = object.value(QString("definition")).toObject();
    int id_action = int(definition.value(QString("actionId")).toInt());
    _action = _database->get_action(id_action);
    _id = int(definition.value(QString("id")).toInt());
    _areaShape = int(definition.value(QString("areaShape")).toInt());
    QJsonArray Array = definition.value(QString("areaSize")).toArray();
    for (QJsonArray::iterator ASit = Array.begin(); ASit != Array.end(); ++ASit) {
        _areaSize.push_back(ASit->toInt());
    }
    Array =  definition.value(QString("params")).toArray();
    for (QJsonArray::iterator ASit = Array.begin(); ASit != Array.end(); ++ASit) {
        _params.push_back(float(ASit->toDouble()));
    }
    if (object.contains(QString("description"))) {
        _description = object.value(QString("description")).toObject().value("fr").toString();
    } else {
        _description = QString();
    }
}

int c_effect::getId() const {
    return _id;
}

c_action c_effect::getAction() const {
    return _action;
}

int c_effect::getAreaShape() const {
    return _areaShape;
}

QVector<int> c_effect::getAreaSize() const {
    return _areaSize;
}

QVector<float> c_effect::getParams() const {
    return _params;
}

QString c_effect::getAreaSize_string() const {
    QString str_areaSize;
    for (QVector<int>::const_iterator it = _areaSize.begin(); it!=_areaSize.end(); ++it) {
        str_areaSize += QString("%1,").arg(*it);
    }
    return str_areaSize.left(str_areaSize.lastIndexOf(','));
}

QString c_effect::getParams_string() const {
    QString str_Params;
    for (QVector<float>::const_iterator it = _params.begin(); it!=_params.end(); ++it) {
        str_Params += QString("%1,").arg(double(*it));
    }
    return str_Params.left(str_Params.lastIndexOf(','));
}

QString c_effect::getDescription() const {
    return _description;
}

void c_effect::setId(const int id) {
    _id = id;
}

void c_effect::setAction(const c_action Actionid) {
    _action = Actionid;
}

void c_effect::setAreaShape(const int AreaShape) {
    _areaShape = AreaShape;
}

void c_effect::setAreaSize(const QVector<int> AreaSize) {
    _areaSize = AreaSize;
}

void c_effect::setParams(const QVector<float> Params) {
    _params = Params;
}

QMap<QString,QString> c_effect::getEffectString(const int lvl) const {
    QMap<QString,QString> res;
    QString text = tokenizer.formatString(_action.getDescription(),_params.toList(),lvl,_action.getDescription().size());
    if (!text.isEmpty()) {
        if (text.toInt()) {
            c_state state = _database->get_state(text.toInt());
            res.insert("text",QString("%1 (Niv. %2)").arg(state.get_name()).arg(double(_params.at(2))));
            res.insert("description",state.get_description());
        } else {
            res.insert("text", text);
            res.insert("description","");
        }
    } else {
        QString descri = tokenizer.formatString(_description,_params.toList(),lvl,_action.getDescription().size());
        int id_state = tokenizer.get_id_state(descri);
        if (id_state) {
            c_state state = _database->get_state(id_state);
            descri = descri.replace(QString("[%1]").arg(id_state),state.get_name());
            res.insert("description",state.get_description());
        } else {
            res.insert("description","");
        }
        res.insert("text",descri);
    }
    return res;
}

void c_effect::setDescrition(const QString descri) {
    _description = descri;
}

QMap<QString,QString> c_effect::interpretState(int state_id) const {
    QMap<QString,QString> res;
    c_state state = _database->get_state(state_id);
    res.insert("text",QString("%1 (Niv. %2)").arg(state.get_name()).arg(double(_params.at(2))));
    res.insert("description",state.get_description());
    return res;
}

QMap<QString, QString> c_effect::getEffectMap(const int lvl) const {
    QMap<QString,QString> map = getEffectString(lvl);
    return tokenizer.interpret_effect(map["text"]);
}
