#include "c_enchantement_effect.h"

c_enchantement_effect::c_enchantement_effect() {
    _id = 0;
    _color = 0;
    _effect = "";
    _valuePerLvl = QList<int>();
    _bonus = QList<QString>();
    _levelingCurve = QList<int> ();
    _levelRequirement = QList<int>();
}

c_enchantement_effect::c_enchantement_effect(QJsonObject object) {
    QJsonObject definition = object.value("definition").toObject();
    QJsonObject item = definition.value("item").toObject();
    QJsonObject shardsParameters = item.value("shardsParameters").toObject();
    QJsonObject useParameter = item.value("useParameters").toObject();

    _id = item.value("id").toInt();
    _color = shardsParameters.value("color").toInt();
    _effect = object.value("title").toObject().value("fr").toString();

    if (_effect.contains("Résistance")) {
        _valuePerLvl = {0, 2, 5, 7, 10, 12, 15, 17, 20, 22, 25};
    } else if (_effect.contains("Esquive") || _effect.contains("Tacle")) {
        _valuePerLvl = {0, 3, 6, 9, 12, 15, 21, 30, 39, 48, 60};
    } else if (_effect.contains("Vie")) {
        _valuePerLvl = {0, 4, 8, 12, 16, 20, 28, 40, 52, 64, 80};
    } else if (_effect.contains("Elémentaire")) {
        _valuePerLvl = {0, 1, 2, 3, 4, 5, 7, 10, 13, 16, 20};
    } else if (_effect.contains("Soin") || _effect.contains("Berserk") || _effect.contains("Initiative")) {
        _valuePerLvl = {0, 2, 4, 6, 8, 10, 14, 20, 26, 32, 40};
    } else {
        _valuePerLvl = {0, 1, 3, 4, 6, 7, 10, 15, 19, 24,30};
    }
    /*_valuePerLvl = definition.value("equipEffects").toArray()
            .takeAt(1).toObject().value("effect").toObject().value("definition")
            .toObject().value("params").toArray().at(1).toDouble();
    if (_valuePerLvl == 0.0) _valuePerLvl = 1.0; *///Fix pour les dégâts élémentaires
    qDebug() << "----------------------" << _effect << "----------------------";
    qDebug() << _id;
    qDebug() << _color;
    qDebug() << _valuePerLvl;

    QJsonArray leveling_array = shardsParameters.value("shardLevelingCurve").toArray();
    for (QJsonArray::iterator it = leveling_array.begin(); it != leveling_array.end(); ++it) {
        _levelingCurve.push_back(it->toInt());
    }

    qDebug() << _levelingCurve;
    qDebug() << levelingCurve_string();
    setLevelingCurve_string(levelingCurve_string());
    qDebug() << _levelingCurve;

    QJsonArray level_requi_array = shardsParameters.value("shardLevelRequirement").toArray();
    for (QJsonArray::iterator it = level_requi_array.begin(); it != level_requi_array.end(); ++it) {
        _levelRequirement.push_back(it->toInt());
    }

    qDebug() << _levelRequirement;
    qDebug() << levelRequirement_string();
    setLevelRequirement_string(levelRequirement_string());
    qDebug() << _levelRequirement;

    QJsonArray bonus_position_array = shardsParameters.value("doubleBonusPosition").toArray();
    for (QJsonArray::iterator it = bonus_position_array.begin(); it != bonus_position_array.end(); ++it) {
        switch ( it->toInt()) {
            case 0:
                _bonus.push_back("HEAD");
                break;
            case 3:
                _bonus.push_back("SHOULDERS");
                break;
            case 4:
                _bonus.push_back("NECK");
                break;
            case 5:
                _bonus.push_back("CHEST");
                break;
            case 7:
                _bonus.push_back("LEFT_HAND");
                break;
            case 8:
                _bonus.push_back("RIGHT_HAND");
                break;
            case 10:
                _bonus.push_back("BELT");
                break;
            case 12:
                _bonus.push_back("LEGS");
                break;
            case 13:
                _bonus.push_back("BACK");
                break;
            case 15:
                _bonus.push_back("FIRST_WEAPON");
                break;
            case 16:
                _bonus.push_back("SECOND_WEAPON");
                break;
            default:
                break;
        }
    }
    qDebug() << _bonus;
    qDebug() << bonus_string();
    setBonus_string(bonus_string());
    qDebug() << _bonus;
}

int c_enchantement_effect::id() const {
    return _id;
}

void c_enchantement_effect::setId(int id) {
    _id = id;
}

int c_enchantement_effect::color() const {
    return _color;
}

void c_enchantement_effect::setColor(int color) {
    _color = color;
}

QString c_enchantement_effect::effect() const {
    return _effect;
}

void c_enchantement_effect::setEffect(const QString &effect) {
    _effect = effect;
    if (_effect.contains("Résistance")) {
        _valuePerLvl = {0, 2, 5, 7, 10, 12, 15, 17, 20, 22, 25};
    } else if (_effect.contains("Esquive") || _effect.contains("Tacle")) {
        _valuePerLvl = {0, 3, 6, 9, 12, 15, 21, 30, 39, 48, 60};
    } else if (_effect.contains("Vie")) {
        _valuePerLvl = {0, 4, 8, 12, 16, 20, 28, 40, 52, 64, 80};
    } else if (_effect.contains("Elémentaire")) {
        _valuePerLvl = {0, 1, 2, 3, 4, 5, 7, 10, 13, 16, 20};
    } else if (_effect.contains("Soin") || _effect.contains("Berserk") || _effect.contains("Initiative")) {
        _valuePerLvl = {0, 2, 4, 6, 8, 10, 14, 20, 26, 32, 40};
    } else {
        _valuePerLvl = {0, 1, 3, 4, 6, 7, 10, 15, 19, 24,30};
    }
}

QList<int> c_enchantement_effect::valuePerLvl() const {
    return _valuePerLvl;
}

QString c_enchantement_effect::valuePerLvl_string() const {
    QString res;
    for (int i = 0; i < _valuePerLvl.size(); ++i) {
        res += QString(" %1").arg(_valuePerLvl[i]);
    }
    return res;
}

void c_enchantement_effect::setValuePerLvl(const QList<int> &valuePerLvl) {
    _valuePerLvl = valuePerLvl;
}

void c_enchantement_effect::setValuePerLvl_string(const QString &valuePerLvl) {
    QStringList list = valuePerLvl.split(" ");
    _valuePerLvl.clear();
    foreach (QString elem, list) {
        if (!elem.isEmpty()) {
            _valuePerLvl.push_back(elem.toInt());
        }
    }
}

QList<QString> c_enchantement_effect::bonus() const {
    return _bonus;
}

QString c_enchantement_effect::bonus_string() const {
    QString res;
    for (int i = 0; i < _bonus.size(); ++i) {
        res += QString(" %1").arg(_bonus[i]);
    }
    return res;
}

void c_enchantement_effect::setBonus(const QList<QString> &bonus) {
    _bonus = bonus;
}

void c_enchantement_effect::setBonus_string(const QString &bonus) {
    QStringList list = bonus.split(" ");
    _bonus.clear();
    foreach (QString elem, list) {
        if (!elem.isEmpty()) {
            _bonus.push_back(elem);
        }
    }
}

QList<int> c_enchantement_effect::levelingCurve() const {
    return _levelingCurve;
}

QString c_enchantement_effect::levelingCurve_string() const {
    QString res;
    for (int i = 0; i < _levelingCurve.size(); ++i) {
        res += QString(" %1").arg(_levelingCurve[i]);
    }
    return res;
}

void c_enchantement_effect::setLevelingCurve(const QList<int> &levelingCurve) {
    _levelingCurve = levelingCurve;
}

void c_enchantement_effect::setLevelingCurve_string(const QString &levelingCurve) {
    QStringList list = levelingCurve.split(" ");
    _levelingCurve.clear();
    foreach (QString elem, list) {
        if (!elem.isEmpty()) {
            _levelingCurve.push_back(elem.toInt());
        }
    }
}

QList<int> c_enchantement_effect::levelRequirement() const {
    return _levelRequirement;
}

QString c_enchantement_effect::levelRequirement_string() const {
    QString res;
    for (int i = 0; i < _levelRequirement.size(); ++i) {
        res += QString(" %1").arg(_levelRequirement[i]);
    }
    return res;
}

void c_enchantement_effect::setLevelRequirement(const QList<int> &levelRequirement) {
    _levelRequirement = levelRequirement;
}

void c_enchantement_effect::setLevelRequirement_string(const QString &levelRequirement) {
    QStringList list = levelRequirement.split(" ");
    _levelRequirement.clear();
    foreach (QString elem, list) {
        if (!elem.isEmpty()) {
            _levelRequirement.push_back(elem.toInt());
        }
    }
}
