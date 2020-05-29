#ifndef C_BUILD_H
#define C_BUILD_H

#include <QObject>
#include "c_item.h"
#include "utilities.h"
#include "c_calcul.h"


class c_build : public QObject
{
    Q_OBJECT

public:
    c_build();
    c_build(const c_build &build);
    ~c_build();

    QMap<QString, int> getBonuses() const;
    void setBonuses(const QMap<QString, int> &value);

    QList<QString> getElements() const;

    QMap<QString, c_item*> getEquipment_pt();
    QMap<QString, c_item> getEquipment() const;
    void setEquipment(const QMap<QString, c_item> &value);

    void computeBonuses();
    QMap<QString,QString> check_constraints(c_item);
    QString getBonusesString();

    bool getEpique_free() const;
    void setEpique_free(bool value);

    bool getRelique_free() const;
    void setRelique_free(bool value);

    c_build& operator=(const c_build& build);
    QMap<QString,int> resetMap();

    int getLvl() const;

private:
    bool epique_free;
    bool relique_free;
    QList<QString> elements;
    QMap<QString,int> bonuses;
    QMap<QString,c_item> equipment;
    int lvl;
    bool nation_bonus;
    bool guilde_bonus;
    bool hm_bonus;

signals:
    void disableSecondWeapon(bool);
    void updated();

public slots:
    QMap<QString,QString> equip(const c_item &item);
    void unequip(QString position);
    void setLvl(int new_lvl);
    void slot_bonus_changed(QList<bool> bonus);
    void setElements(const QList<QString> &value);
    void slot_item_element_changed();

};

#endif // C_BUILD_H
