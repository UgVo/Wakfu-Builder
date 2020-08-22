#include "c_build.h"

c_build::c_build() {

    elements << "Feu" << "Eau"
             << "Terre" << "Air";

    equipment["FIRST_WEAPON"] = c_item();
    equipment["SECOND_WEAPON"] = c_item();
    equipment["LEFT_HAND"] = c_item();
    equipment["RIGHT_HAND"] = c_item();
    equipment["LEGS"] = c_item();
    equipment["NECK"] = c_item();
    equipment["BACK"] = c_item();
    equipment["BELT"] = c_item();
    equipment["HEAD"] = c_item();
    equipment["CHEST"] = c_item();
    equipment["SHOULDERS"] = c_item();
    equipment["ACCESSORY"] = c_item();
    equipment["PET"] = c_item();
    equipment["MOUNT"] = c_item();

    epique_free = true;
    relique_free = true;

    lvl = 0;
    nation_bonus = false;
    guilde_bonus = false;
    hm_bonus = false;

    bonuses = resetMap();
    init_bonus_aptitudes();
}

c_build::c_build(const c_build &build) {
    bonuses = build.getBonuses();
    elements = build.getElements();
    equipment = build.getEquipment();
    epique_free = build.getEpique_free();
    relique_free = build.getRelique_free();
}

c_build::~c_build() {

}

QMap<QString, int> c_build::getBonuses() const {
    QMap<QString, int> bonus_global;

    bonus_global["Vie"] = int(qreal(bonuses["Vie"] + bonus_aptitudes["Point de Vie"]*20) * ((qreal(bonus_aptitudes["% Point de Vie"]*4)/100.0) + 1.0));
    bonus_global["PA"] = bonuses["PA"] + bonus_aptitudes["Point d'action"];
    bonus_global["PM"] = bonuses["PM"] + bonus_aptitudes["Point de Mouvement et dégâts"];
    bonus_global["PW"] = bonuses["PW"] + bonus_aptitudes["Point de Wakfu"]*2;
    bonus_global["Maîtrise Élémentaire Feu"] = bonuses["Maîtrise Élémentaire Feu"] +  bonus_aptitudes["Maitrise Élémentaire"]*5 + bonus_aptitudes["Point de Mouvement et dégâts"]*20 + bonus_aptitudes["Portée et dégâts"]*40 + bonus_aptitudes["Contrôle et dégâts"]*40;
    bonus_global["Maîtrise Élémentaire Eau"] = bonuses["Maîtrise Élémentaire Eau"] +  bonus_aptitudes["Maitrise Élémentaire"]*5 + bonus_aptitudes["Point de Mouvement et dégâts"]*20 + bonus_aptitudes["Portée et dégâts"]*40 + bonus_aptitudes["Contrôle et dégâts"]*40;
    bonus_global["Maîtrise Élémentaire Terre"] = bonuses["Maîtrise Élémentaire Terre"] +  bonus_aptitudes["Maitrise Élémentaire"]*5 + bonus_aptitudes["Point de Mouvement et dégâts"]*20 + bonus_aptitudes["Portée et dégâts"]*40 + bonus_aptitudes["Contrôle et dégâts"]*40;
    bonus_global["Maîtrise Élémentaire Air"] = bonuses["Maîtrise Élémentaire Air"] +  bonus_aptitudes["Maitrise Élémentaire"]*5 + bonus_aptitudes["Point de Mouvement et dégâts"]*20 + bonus_aptitudes["Portée et dégâts"]*40 + bonus_aptitudes["Contrôle et dégâts"]*40;
    bonus_global["Résistance Feu"] = bonuses["Résistance Feu"] + bonus_aptitudes["Résistance Élémentaire"]*10 + bonus_aptitudes["Résistance Élémentaire majeur"]*50;
    bonus_global["Résistance Eau"] = bonuses["Résistance Eau"] + bonus_aptitudes["Résistance Élémentaire"]*10 + bonus_aptitudes["Résistance Élémentaire majeur"]*50;
    bonus_global["Résistance Terre"] = bonuses["Résistance Terre"] + bonus_aptitudes["Résistance Élémentaire"]*10 + bonus_aptitudes["Résistance Élémentaire majeur"]*50;
    bonus_global["Résistance Air"] = bonuses["Résistance Air"] + bonus_aptitudes["Résistance Élémentaire"]*10 + bonus_aptitudes["Résistance Élémentaire majeur"]*50;
    bonus_global["Dommages infligés"] = bonuses["Dommages infligés"] + bonus_aptitudes["% Dommages infligés"]*10;
    bonus_global["Soins réalisés"] = bonuses["Soins réalisés"];
    bonus_global["Parade"] = bonuses["Parade"] + bonus_aptitudes["% Parade"];
    bonus_global["Coup Critique"] = bonuses["Coup Critique"] + bonus_aptitudes["% Coup Critique"];
    bonus_global["Initiative"] = bonuses["Initiative"] + bonus_aptitudes["Initiative"]*4;
    bonus_global["Portée"] = bonuses["Portée"] + bonus_aptitudes["Portée et dégâts"];
    bonus_global["Esquive"] = bonuses["Esquive"] + bonus_aptitudes["Esquive"]*6 + bonus_aptitudes["Tacle et Esquive"]*4;
    bonus_global["Tacle"] = bonuses["Tacle"] + bonus_aptitudes["Tacle"]*6 + bonus_aptitudes["Tacle et Esquive"]*4;
    bonus_global["Sagesse"] = bonuses["Sagesse"];
    bonus_global["Prospection"] = bonuses["Prospection"];
    bonus_global["Contrôle"] = bonuses["Contrôle"] + bonus_aptitudes["Contrôle et dégâts"]*2;
    bonus_global["Art du barda"] = bonuses["Art du barda"];
    bonus_global["Volonté"] = bonuses["Volonté"] + bonus_aptitudes["Volonté"];
    bonus_global["Maîtrise Critique"] = bonuses["Maîtrise Critique"] + bonus_aptitudes["Maîtrise Critique"]*4;
    bonus_global["Résistance Critique"] = bonuses["Résistance Critique"] + bonus_aptitudes["Résistance Critique"]*4;
    bonus_global["Maîtrise Dos"] = bonuses["Maîtrise Dos"] + bonus_aptitudes["Maîtrise Dos"]*6;
    bonus_global["Résistance Dos"] = bonuses["Résistance Dos"] + bonus_aptitudes["Résistance Dos"]*4;
    bonus_global["Maîtrise Mêlée"] = bonuses["Maîtrise Mêlée"] + bonus_aptitudes["Maitrise Mêlée"]*8;
    bonus_global["Maîtrise Distance"] = bonuses["Maîtrise Distance"] + bonus_aptitudes["Maitrise Distance"]*8;
    bonus_global["Maîtrise Monocible"] = bonuses["Maîtrise Monocible"] +  bonus_aptitudes["Maitrise Monocible"]*8;
    bonus_global["Maîtrise Zone"] = bonuses["Maîtrise Zone"] + bonus_aptitudes["Maitrise Zone"]*8;
    bonus_global["Maîtrise Soin"] = bonuses["Maîtrise Soin"] + bonus_aptitudes["Maîtrise Soin"]*6;
    bonus_global["Maîtrise Berserk"] = bonuses["Maîtrise Berserk"] + bonus_aptitudes["Maîtrise Berserk"]*8;
    bonus_global["Niv. aux sorts Feu"] = bonuses["Niv. aux sorts Feu"];
    bonus_global["Niv. aux sorts Eau"] = bonuses["Niv. aux sorts Eau"];
    bonus_global["Niv. aux sorts Terre"] = bonuses["Niv. aux sorts Terre"];
    bonus_global["Niv. aux sorts Air"] = bonuses["Niv. aux sorts Air"];
    bonus_global["Armure donnée"] = bonuses["Armure donnée"];
    bonus_global["Armure reçue"] = bonuses["Armure reçue"];
    bonus_global["Armure"] = int(qreal(bonuses["Vie"]) * qreal(bonus_aptitudes["% Point de Vie en Armure"]*4)/100.0);

    foreach (QString key, bonus_enchant.keys()) {
        bonus_global[key] += bonus_enchant[key];
    }
    return bonus_global;
}

void c_build::setBonuses(const QMap<QString, int> &value) {
    bonuses = value;
}

QList<QString> c_build::getElements() const {
    return elements;
}

void c_build::setElements(const QList<QString> &value) {
    elements = value;
}

QMap<QString, c_item*> c_build::getEquipment_pt() {
    QMap<QString,c_item*> res;
    foreach(QString key, equipment.keys()) {
        res[key] = &equipment[key];
    }
    return res;
}

QMap<QString, c_item> c_build::getEquipment() const {
    return equipment;
}

void c_build::setEquipment(const QMap<QString, c_item> &value) {
    equipment = value;
}

void c_build::computeBonuses() {
    QMap<QString,int> item_bonuses;
    QList<QString> item_element;
    bonuses = resetMap();
    foreach (c_item item, equipment) {
        item_bonuses = item.getBonuses();
        item_element = item.getElements();
        foreach (QString key, item_bonuses.keys()) {
            if (!key.isEmpty()) {
                if (!key.contains("éléments") && !key.contains("Élémentaire")) {
                    bonuses[key] += item_bonuses[key];
                } else if (!key.compare("Maîtrise sur 1 éléments")) {
                    bonuses["Maîtrise Élémentaire " + item_element.at(0)] += item_bonuses[key];
                } else if (!key.compare("Maîtrise sur 2 éléments")) {
                    bonuses["Maîtrise Élémentaire " + item_element.at(0)] += item_bonuses[key];
                    bonuses["Maîtrise Élémentaire " + item_element.at(1)] += item_bonuses[key];
                } else if (!key.compare("Maîtrise sur 3 éléments")) {
                    bonuses["Maîtrise Élémentaire " + item_element.at(0)] += item_bonuses[key];
                    bonuses["Maîtrise Élémentaire " + item_element.at(1)] += item_bonuses[key];
                    bonuses["Maîtrise Élémentaire " + item_element.at(2)] += item_bonuses[key];
                } else if (!key.compare("Maîtrise Élémentaire")) {
                    bonuses["Maîtrise Élémentaire " + item_element.at(0)] += item_bonuses[key];
                    bonuses["Maîtrise Élémentaire " + item_element.at(1)] += item_bonuses[key];
                    bonuses["Maîtrise Élémentaire " + item_element.at(2)] += item_bonuses[key];
                    bonuses["Maîtrise Élémentaire " + item_element.at(3)] += item_bonuses[key];
                } else if (!key.compare("Résistance sur 1 éléments")) {
                    bonuses["Résistance " + item_element.at(0)] += item_bonuses[key];
                } else if (!key.compare("Résistance sur 2 éléments")) {
                    bonuses["Résistance " + item_element.at(0)] += item_bonuses[key];
                    bonuses["Résistance " + item_element.at(1)] += item_bonuses[key];
                } else if (!key.compare("Résistance sur 3 éléments")) {
                    bonuses["Résistance " + item_element.at(0)] += item_bonuses[key];
                    bonuses["Résistance " + item_element.at(1)] += item_bonuses[key];
                    bonuses["Résistance " + item_element.at(2)] += item_bonuses[key];
                } else if (!key.compare("Résistance Élémentaire")) {
                    bonuses["Résistance " + item_element.at(0)] += item_bonuses[key];
                    bonuses["Résistance " + item_element.at(1)] += item_bonuses[key];
                    bonuses["Résistance " + item_element.at(2)] += item_bonuses[key];
                    bonuses["Résistance " + item_element.at(3)] += item_bonuses[key];
                }
            }
        }
    }
}

QMap<QString, QString> c_build::equip(const c_item &item) {
    QMap<QString,QString> res;
    c_item item2equip = item;
    if (item2equip.getElements().isEmpty()) {
        item2equip.setElements(elements);
    }
    QString type = mapItemToType[item2equip.getType().getTitle()];
    res = check_constraints(item2equip);
    if (res["status"] == "error") {
        return res;
    }
    if (!type.compare("SECOND_HAND")) {
        if (!equipment["FIRST_WEAPON"].isEmpty()) {
            if (!mapItemToType[equipment["FIRST_WEAPON"].getType().getTitle()].compare("TWO_HAND_WEAPON")) {
                unequip("FIRST_WEAPON");
                equipment["SECOND_WEAPON"] = item2equip;
                emit disableSecondWeapon(false);
            } else {
                unequip("SECOND_WEAPON");
                equipment["SECOND_WEAPON"] = item2equip;
            }
        } else {
            unequip("SECOND_WEAPON");
            equipment["SECOND_WEAPON"] = item2equip;
        }
    } else if (!type.compare("RING")) {
        if (equipment["LEFT_HAND"].isEmpty()) {
            equipment["LEFT_HAND"] = item2equip;
        } else if (equipment["RIGHT_HAND"].isEmpty()){
            equipment["RIGHT_HAND"] = item2equip;
        }else {
            unequip("LEFT_HAND");
            equipment["LEFT_HAND"] = item2equip;
        }
    } else if (!type.compare("ONE_HAND_WEAPON")) {
        unequip("FIRST_WEAPON");
        equipment["FIRST_WEAPON"] = item2equip;
        emit disableSecondWeapon(false);
    } else if (!type.compare("TWO_HAND_WEAPON")) {
        unequip("FIRST_WEAPON");
        unequip("SECOND_WEAPON");
        equipment["FIRST_WEAPON"] = item2equip;
        emit disableSecondWeapon(true);
    } else {
        unequip(type);
        equipment[type] = item2equip;
    }
    if (item2equip.getRarity() == 5) {
        relique_free = false;
    } else if(item2equip.getRarity() == 7) {
        epique_free = false;
    }
    computeBonuses();
    emit updated();
    return res;
}

void c_build::unequip(QString position) {
    if (!equipment[position].isEmpty()) {
        c_item item = equipment[position];
        if (!mapItemToType[item.getType().getTitle()].compare("TWO_HAND_WEAPON")) {
            emit disableSecondWeapon(false);
        }
        equipment[position] = c_item();
        if (item.getRarity() == 5) {
            relique_free = true;
        } else if(item.getRarity() == 7) {
            epique_free = true;
        }
        computeBonuses();
    }
    emit updated();
}

QMap<QString,QString> c_build::check_constraints(c_item item) {
    QMap<QString,QString> res;
    if (lvl + bonuses["Art du barda"] < item.getLvl()) {
        res["status"] = "error";
        res["error"] = "Lvl too low";
        res["message"] = "Vous ne pouvez pas équiper cet objet : son niveau est trop élevé par rapport à votre build";
        return res;
    }
    QString position = mapItemToType[item.getType().getTitle()];
    // check unicité des anneaux
    if (!position.compare("RING")) {
        if (item.getId() == equipment["RIGHT_HAND"].getId()
                || item.getId() == equipment["LEFT_HAND"].getId()) {
            res["status"] = "error";
            res["error"] = "Unicity contraint violated";
            res["message"] = "Vous ne pouvez pas équiper cet objet : vous portez déjà un objet identique";
            return res;
        }
    }
    // check unicité de la relique et de l'épique
    if (item.getRarity() == 5 && !relique_free) { //Relique
        res["status"] = "error";
        res["error"] = "Rarity constraint violated";
        res["message"] = "Vous ne pouvez pas équiper cet objet : vous portez déjà une Relique";
        return res;
    } else if (item.getRarity() == 7 && !epique_free) { //Epique
        res["status"] = "error";
        res["error"] = "Rarity constraint violated";
        res["message"] = "Vous ne pouvez pas équiper cet objet : vous portez déjà une Relique";
        return res;
    }
    // check des contraintes spécifiques à l'item
    if (!item.getConstraints().isEmpty()) {
        // Add some return statments that take the specific object constraints in consideration
    }
    res["status"] = "ok";
    return res;
}

QString c_build::getBonusesString() {
    QString res;
    foreach(QString key, bonuses.keys()) {
        res += QString("%1 : %2 \n").arg(key).arg(bonuses[key]);
    }
    return res;
}

bool c_build::getEpique_free() const
{
    return epique_free;
}

void c_build::setEpique_free(bool value)
{
    epique_free = value;
}

bool c_build::getRelique_free() const
{
    return relique_free;
}

void c_build::setRelique_free(bool value)
{
    relique_free = value;
}

c_build& c_build::operator=(const c_build& build) {
    if (&build != this) {
        bonuses = build.getBonuses();
        elements = build.getElements();
        equipment = build.getEquipment();
        epique_free = build.getEpique_free();
        relique_free = build.getRelique_free();
    }
    return *this;
}

QMap<QString,int> c_build::resetMap() {
    bonuses.clear();
    bonuses["Vie"] = c_calcul::compute_life(lvl) + (guilde_bonus?55:0) + (nation_bonus?20:0);
    bonuses["PA"] = 6;
    bonuses["PM"] = 3;
    bonuses["PW"] = 6;
    bonuses["Maîtrise Élémentaire Feu"] = 0 ;
    bonuses["Maîtrise Élémentaire Eau"] = 0;
    bonuses["Maîtrise Élémentaire Terre"] = 0;
    bonuses["Maîtrise Élémentaire Air"] = 0;
    bonuses["Résistance Feu"] = 0 + (guilde_bonus?20:0);
    bonuses["Résistance Eau"] = 0 + (guilde_bonus?20:0);
    bonuses["Résistance Terre"] = 0 + (guilde_bonus?20:0);
    bonuses["Résistance Air"] = 0 + (guilde_bonus?20:0);
    bonuses["Dommages infligés"] = 0 + (guilde_bonus?8:0) + (nation_bonus?5:0);
    bonuses["Soins réalisés"] = 0 + (guilde_bonus?8:0);
    bonuses["Parade"] = 0;
    bonuses["Coup Critique"] = 3;
    bonuses["Initiative"] = 0 + (guilde_bonus?10:0);
    bonuses["Portée"] = 0;
    bonuses["Esquive"] = 0 + (guilde_bonus?20:0);
    bonuses["Tacle"] = 0 + (guilde_bonus?20:0);
    bonuses["Sagesse"] = 0 + (guilde_bonus?10:0) + (hm_bonus?10:0);
    bonuses["Prospection"] = 0 + (guilde_bonus?10:0) + (hm_bonus?10:0);
    bonuses["Contrôle"] = 1;
    bonuses["Art du barda"] = 0 + (guilde_bonus?2:0) + (hm_bonus?1:0);
    bonuses["Volonté"] = 0;
    bonuses["Maîtrise Critique"] = 0;
    bonuses["Résistance Critique"] = 0;
    bonuses["Maîtrise Dos"] = 0;
    bonuses["Résistance Dos"] = 0;
    bonuses["Maîtrise Mêlée"] = 0;
    bonuses["Maîtrise Distance"] = 0;
    bonuses["Maîtrise Monocible"] = 0;
    bonuses["Maîtrise Zone"] = 0;
    bonuses["Maîtrise Soin"] = 0;
    bonuses["Maîtrise Berserk"] = 0;
    bonuses["Niv. aux sorts Feu"] = 0;
    bonuses["Niv. aux sorts Eau"] = 0;
    bonuses["Niv. aux sorts Terre"] = 0;
    bonuses["Niv. aux sorts Air"] = 0;
    bonuses["Armure donnée"] = 0;
    bonuses["Armure reçue"] = 0;
    return bonuses;
}

void c_build::init_bonus_aptitudes() {
    bonus_aptitudes["% Point de Vie"] = 0;
    bonus_aptitudes["Résistance Élémentaire"] = 0;
    bonus_aptitudes["Barrière"] = 0;
    bonus_aptitudes["% Soin Reçu"] = 0;
    bonus_aptitudes["% Point de Vie en Armure"] = 0;

    bonus_aptitudes["Maitrise Élémentaire"] = 0;
    bonus_aptitudes["Maitrise Monocible"] = 0;
    bonus_aptitudes["Maitrise Zone"] = 0;
    bonus_aptitudes["Maitrise Mêlée"] = 0;
    bonus_aptitudes["Maitrise Distance"] = 0;
    bonus_aptitudes["Point de Vie"] = 0;

    bonus_aptitudes["Tacle"] = 0;
    bonus_aptitudes["Esquive"] = 0;
    bonus_aptitudes["Initiative"] = 0;
    bonus_aptitudes["Tacle et Esquive"] = 0;
    bonus_aptitudes["Volonté"] = 0;

    bonus_aptitudes["% Coup Critique"] = 0;
    bonus_aptitudes["% Parade"] = 0;
    bonus_aptitudes["Maîtrise Critique"] = 0;
    bonus_aptitudes["Maîtrise Dos"] = 0;
    bonus_aptitudes["Maîtrise Berserk"] = 0;
    bonus_aptitudes["Maîtrise Soin"] = 0;
    bonus_aptitudes["Résistance Dos"] = 0;
    bonus_aptitudes["Résistance Critique"] = 0;

    bonus_aptitudes["Point d'action"] = 0;
    bonus_aptitudes["Point de Mouvement et dégâts"] = 0;
    bonus_aptitudes["Portée et dégâts"] = 0;
    bonus_aptitudes["Point de Wakfu"] = 0;
    bonus_aptitudes["Contrôle et dégâts"] = 0;
    bonus_aptitudes["% Dommages infligés"] = 0;
    bonus_aptitudes["Résistance Élémentaire majeur"] = 0;
}

int c_build::getLvl() const {
    return lvl;
}

QMap<QString, int> c_build::getBonus_aptitudes() const {
    return bonus_aptitudes;
}

void c_build::setBonus_enchant(const QMap<QString, int> &value) {
    bonus_enchant = value;
    computeBonuses();
    emit updated();
}

void c_build::setLvl(int new_lvl) {
    lvl = new_lvl;
    computeBonuses();
    emit updated();
}

void c_build::slot_bonus_changed(QList<bool> bonus) {
    nation_bonus = bonus.at(0);
    guilde_bonus = bonus.at(1);
    hm_bonus = bonus.at(2);
    computeBonuses();
    emit updated();
}

void c_build::slot_item_element_changed() {
    computeBonuses();
    emit updated();
}

void c_build::slot_aptitude_value_changed(QString type, int value) {
    bonus_aptitudes[type] = value;
    computeBonuses();
    emit updated();
}