#ifndef C_ENCHANTEMENT_EFFECT_H
#define C_ENCHANTEMENT_EFFECT_H

#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class c_enchantement_effect
{
public:
    c_enchantement_effect();
    c_enchantement_effect(QJsonObject object);

    int id() const;
    void setId(int id);

    int color() const;
    void setColor(int color);

    QString effect() const;
    void setEffect(const QString &effect);

    QList<int> valuePerLvl() const;
    QString valuePerLvl_string() const;
    void setValuePerLvl(const QList<int> &valuePerLvl);
    void setValuePerLvl_string(const QString &valuePerLvl);

    QList<QString> bonus() const;
    QString bonus_string() const;
    void setBonus(const QList<QString> &bonus);
    void setBonus_string(const QString &bonus);

    QList<int> levelingCurve() const;
    QString levelingCurve_string() const;
    void setLevelingCurve(const QList<int> &levelingCurve);
    void setLevelingCurve_string(const QString &levelingCurve);

    QList<int> levelRequirement() const;
    QString levelRequirement_string() const;
    void setLevelRequirement(const QList<int> &levelRequirement);
    void setLevelRequirement_string(const QString &levelRequirement);

private:
    int _id;
    int _color;
    QString _effect;
    QList<int> _valuePerLvl;
    QList<QString> _bonus;
    QList<int> _levelingCurve;
    QList<int> _levelRequirement;
};

#endif // C_ENCHANTEMENT_EFFECT_H
