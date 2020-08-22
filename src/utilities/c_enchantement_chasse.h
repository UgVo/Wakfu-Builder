#ifndef C_ENCHANTEMENT_CHASSE_H
#define C_ENCHANTEMENT_CHASSE_H

#include "c_enchantement_effect.h"
#include <QtMath>

class c_enchantement_chasse
{
public:
    c_enchantement_chasse(int level = 0, c_enchantement_effect effect = c_enchantement_effect());

    int color() const;
    void setColor(int color);

    void setLevel(int level);
    void setChasseLevel(int level);
    QMap<QString,int> computeBonus(QString position);

    c_enchantement_effect effect() const;
    void setEffect(const c_enchantement_effect &effect);

    int level() const;

    bool white() const;
    void setWhite(bool white);

private:
    int _color;
    int _level;
    bool _white;
    c_enchantement_effect _effect;
};

#endif // C_ENCHANTEMENT_CHASSE_H
