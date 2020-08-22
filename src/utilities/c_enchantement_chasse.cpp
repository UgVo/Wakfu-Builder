#include "c_enchantement_chasse.h"

c_enchantement_chasse::c_enchantement_chasse(int level, c_enchantement_effect effect) {
    _level = level;
    _color = effect.color();
    _effect = effect;
    _white = false;
}

int c_enchantement_chasse::color() const
{
    return _color;
}

void c_enchantement_chasse::setLevel(int item_level) {
    if (_color) {
        QList<int> lvlCurve = _effect.levelRequirement();
        int lvl = 0;
        while (lvlCurve[lvl] < item_level && lvl <= lvlCurve.size()-1) {
            lvl++;
        }
        _level = lvl;
    }
}

void c_enchantement_chasse::setChasseLevel(int level) {
    _level = level;
}

QMap<QString, int> c_enchantement_chasse::computeBonus(QString position) {
    if (!_color) return QMap<QString, int>();
    int coef = (_effect.bonus().contains(position)?2:1);
    QMap<QString,int> res;
    res.insert(_effect.effect(),_effect.valuePerLvl()[_level]*coef);
    qDebug() << res << _color << coef << _level;
    return res;
}

c_enchantement_effect c_enchantement_chasse::effect() const
{
    return _effect;
}

int c_enchantement_chasse::level() const
{
    return _level;
}

bool c_enchantement_chasse::white() const
{
    return _white;
}

void c_enchantement_chasse::setWhite(bool white)
{
    _white = white;
}

void c_enchantement_chasse::setEffect(const c_enchantement_effect &effect)
{
    _effect = effect;
}

void c_enchantement_chasse::setColor(int color)
{
    _color = color;
}
