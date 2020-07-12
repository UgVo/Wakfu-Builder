#include "c_calcul.h"
#include "c_build.h"

c_calcul::c_calcul() {
    _build = nullptr;
    _tc_resume = nullptr;
    _mainMastery << "Maîtrise Élémentaire Feu" << "Maîtrise Mêlée" << "Maîtrise Monocible";
    _healingElementMastery = "Maîtrise Élémentaire Eau";
}

int c_calcul::compute_reduction(const int resistances) {
    int res;
    res = qFloor(100*(1-qPow(0.8,qreal(resistances)/100.0)));
    return res;
}

int c_calcul::compute_life(const int niveau) {
    return 50 + niveau * 10;
}

void c_calcul::setBuild(c_build *build) {
    _build = build;
}

void c_calcul::computeMainMastery() {
    QMap<QString,int> bonuses = _build->getBonuses();
    QList<int> masteryValues;
    _mainMastery.clear();
    _mainMastery << "Maîtrise Élémentaire Feu" << "Maîtrise Mêlée" << "Maîtrise Monocible";
    masteryValues.clear();
    masteryValues << bonuses["Maîtrise Élémentaire Feu"] << bonuses["Maîtrise Mêlée"] << bonuses["Maîtrise Monocible"];

    if (bonuses["Maîtrise Élémentaire Air"] > masteryValues[0]) {
        masteryValues.replace(0,bonuses["Maîtrise Élémentaire Air"]);
        _mainMastery.replace(0,"Maîtrise Élémentaire Air");
    }
    if (bonuses["Maîtrise Élémentaire Eau"] > masteryValues[0]) {
        masteryValues.replace(0,bonuses["Maîtrise Élémentaire Eau"]);
        _mainMastery.replace(0,"Maîtrise Élémentaire Eau");
    }
    if (bonuses["Maîtrise Élémentaire Terre"] > masteryValues[0]) {
        masteryValues.replace(0,bonuses["Maîtrise Élémentaire Terre"]);
        _mainMastery.replace(0,"Maîtrise Élémentaire Terre");
    }

    if (bonuses["Maîtrise Distance"] > masteryValues[1]) {
        masteryValues.replace(1,bonuses["Maîtrise Distance"]);
        _mainMastery.replace(1,"Maîtrise Distance");
    }

    if (bonuses["Maîtrise Zone"] > masteryValues[2]) {
        masteryValues.replace(2,bonuses["Maîtrise Zone"]);
        _mainMastery.replace(2,"Maîtrise Zone");
    }

    qDebug() << _mainMastery;
    computeDamage(100);
}

void c_calcul::computeDamage(int attaqueValue) {
    QMap<QString,int> bonuses = _build->getBonuses();
    qreal baseMastery = qreal(bonuses[_mainMastery[0]] + bonuses[_mainMastery[1]] + bonuses[_mainMastery[2]])/100.0;
    qreal critiqueMatery = qreal(bonuses["Maîtrise Critique"])/100.0;
    qreal backMastery = qreal(bonuses["Maîtrise Dos"])/100.0;
    qreal critiqueRate = qreal(bonuses["Coup Critique"])/100.0;
    qreal damageBonus = 1 + qreal(bonuses["Dommages infligés"])/100.0;
    qreal berserkerMastery = qreal(bonuses["Maîtrise Berserk"])/100.0;
    qreal healMastery = qreal(bonuses["Maîtrise Soin"] + bonuses[_healingElementMastery] + bonuses[_mainMastery[1]] + bonuses[_mainMastery[2]])/100.0;
    qreal healBonus = 1 + qreal(bonuses["Soins réalisés"])/100.0;

    _damages.clear();

// Not Berserk
    qDebug() << "baseMastery" << baseMastery;
    _damages.insert("Front", (baseMastery + 1.0) * damageBonus * attaqueValue );
    _damages.insert("Front Critique", (baseMastery + critiqueMatery + 1.0) * 1.25 * damageBonus * attaqueValue );
    _damages.insert("Front Mean", _damages["Front"] * (1-critiqueRate) + _damages["Front Critique"] * critiqueRate);

    _damages.insert("Side", (baseMastery + 1.0) * damageBonus * attaqueValue * 1.1 );
    _damages.insert("Side Critique", (baseMastery + critiqueMatery + 1.0) * 1.25 * damageBonus * attaqueValue * 1.1 );
    _damages.insert("Side Mean", _damages["Side"] * (1-critiqueRate) + _damages["Side Critique"] * critiqueRate);

    _damages.insert("Back", (baseMastery + backMastery + 1.0) * damageBonus * attaqueValue * 1.25 );
    _damages.insert("Back Critique", (baseMastery + backMastery + critiqueMatery + 1.0) * 1.25 * damageBonus * attaqueValue * 1.25 );
    _damages.insert("Back Mean", _damages["Back"] * (1-critiqueRate) + _damages["Back Critique"] * critiqueRate);

// Berserk
    baseMastery += berserkerMastery;

    _damages.insert("Berserk Front", (baseMastery + 1.0) * damageBonus * attaqueValue );
    _damages.insert("Berserk Front Critique", (baseMastery + critiqueMatery + 1.0) * 1.25 * damageBonus * attaqueValue );
    _damages.insert("Berserk Front Mean", _damages["Berserk Front"] * (1-critiqueRate) + _damages["Berserk Front Critique"] * critiqueRate);

    _damages.insert("Berserk Side", (baseMastery + 1.0) * damageBonus * attaqueValue * 1.1 );
    _damages.insert("Berserk Side Critique", (baseMastery + critiqueMatery + 1.0) * 1.25 * damageBonus * attaqueValue * 1.1 );
    _damages.insert("Berserk Side Mean", _damages["Berserk Side"] * (1-critiqueRate) + _damages["Berserk Side Critique"] * critiqueRate);

    _damages.insert("Berserk Back", (baseMastery + backMastery + 1.0) * damageBonus * attaqueValue * 1.25 );
    _damages.insert("Berserk Back Critique", (baseMastery + backMastery + critiqueMatery + 1.0) * 1.25 * damageBonus * attaqueValue * 1.25 );
    _damages.insert("Berserk Back Mean", _damages["Berserk Back"] * (1-critiqueRate) + _damages["Berserk Back Critique"] * critiqueRate);

    qDebug() << healMastery;
    _damages.insert("Heal", (1.0 + healMastery) * healBonus * attaqueValue);
    _damages.insert("Heal Critique", (1.0 + healMastery + critiqueMatery) * healBonus * attaqueValue * 1.25);
    _damages.insert("Heal Mean", _damages["Heal"] * (1-critiqueRate) +  _damages["Heal Critique"] * critiqueRate);

    _damages.insert("Berserk Heal", (1.0 + healMastery + berserkerMastery) * healBonus * attaqueValue);
    _damages.insert("Berserk Heal Critique", (1.0 + healMastery + critiqueMatery + berserkerMastery) * healBonus * attaqueValue * 1.25);
    _damages.insert("Berserk Heal Mean", _damages["Berserk Heal"] * (1-critiqueRate) +  _damages["Berserk Heal Critique"] * critiqueRate);

    qDebug() << _damages;

    if(_tc_resume != nullptr) {
        _tc_resume->setValues(_damages);
    }
}

void c_calcul::setTc_resume(c_theory_craft_resume *value)
{
    _tc_resume = value;
}
