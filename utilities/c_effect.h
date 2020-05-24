#ifndef C_EFFECT_H
#define C_EFFECT_H

#include "c_action.h"

#include <QMap>
#include <QString>
#include <QVector>
#include <QDebug>

class c_dbmanager;

class c_effect
{
public:
    c_effect(c_dbmanager *dbmanager, int id = 0, c_action action = c_action(),
             int areaShape = 0, QVector<int> areaSize = QVector<int>(),
             QVector<float> params = QVector<float>(), QString description = QString());
    c_effect(QJsonObject object, c_dbmanager *dbmanager);
    int getId() const;
    c_action getAction()const;
    int getAreaShape()const;
    QVector<int> getAreaSize()const;
    QVector<float> getParams()const;
    QString getAreaSize_string()const;
    QString getParams_string()const;
    QString getDescription()const;
    void setId(const int id);
    void setAction(const c_action Actionid);
    void setAreaShape(const int AreaShape);
    void setAreaSize(const QVector<int> AreaSize);
    void setParams(const QVector<float> Params);
    void setDescrition(const QString descri);


    QMap<QString,QString> getEffectString(const int lvl) const;
    QMap<QString,QString> interpretState(int state_id) const;
    QMap<QString,QString> getEffectMap(const int lvl) const;
private:

    int _id;
    c_action _action;
    int _areaShape;
    QVector<int> _areaSize;
    QVector<float> _params;
    QString _description;
    c_dbmanager* _database;
    c_tokenizer tokenizer;
};

#endif // C_EFFECT_H
