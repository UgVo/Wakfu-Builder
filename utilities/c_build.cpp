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
    return bonuses;
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
    bonuses["Maîtrise Mélée"] = 0;
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

int c_build::getLvl() const {
    return lvl;
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
