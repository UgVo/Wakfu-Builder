#ifndef C_ITEM_H
#define C_ITEM_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include "c_effect.h"
#include "c_itemproperties.h"
#include "c_equipmentitemtypes.h"

class c_dbmanager;

class c_carac {
public :
    c_carac(int _id = 0, QString _effect = QString(),int _value = 0) {
        id = _id;
        effect = _effect;
        value = _value;
    }
    int id;
    QString effect;
    int value;
};

class c_item
{
public:
    c_item(int id = 0,int lvl = 0, QString name = QString(), QString description = QString(),
           c_equipmentItemTypes itemType = c_equipmentItemTypes(), int itemSetId = 0,
           int rarity = 0, bool bindType = false, int minShNum = 0,
           int maxShNum = 4, int ApCost = 0, int MpCost = 0,
           int WpCost = 0, int minRange = 0, int maxRange = 0,
           bool testFreeCell = false, bool testLos = false, bool testOnlyLine = false,
           bool testNoBorderCell = true, int worldTarget = 0, int gfxId = 0,
           QVector<c_itemProperties> properties = QVector<c_itemProperties>(),
           QVector<c_effect> useEffects = QVector<c_effect>(),
           QVector<c_effect> useCriticalEffects = QVector<c_effect>(),
           QVector<c_effect> equipEffects = QVector<c_effect>());
    c_item(QJsonObject object, c_dbmanager *dbManager);

    const static QString FIRST_WEAPON;
    const static QString SECOND_WEAPON;
    const static QString LEFT_HAND;
    const static QString RIGHT_HAND;
    const static QString LEGS;
    const static QString NECK;
    const static QString BACK;
    const static QString BELT;
    const static QString HEAD;
    const static QString CHEST;
    const static QString SHOULDERS;
    const static QString ACCESSORY;
    const static QString PET;
    const static QString MOUNT;
    const static QString NONE;

//    enum class positions {FIRST_WEAPON, SECOND_WEAPON, LEFT_HAND, RIGHT_HAND,
//                          LEGS,NECK, BACK, BELT, HEAD, CHEST, SHOULDERS,
//                          ACCESSORY, PET, NONE};

private:

    int _id;
    int _lvl;
    QString _name;
    QString _description;

    c_equipmentItemTypes _itemType;
    int _itemSetId;
    int _rarity;
    int _bindType;
    int _minimumShardSlotNumber;
    int _maximumShardSlotNumber;

    int _useApCost;
    int _useMpCost;
    int _useWpCost;
    int _useMinRange;
    int _useMaxRange;
    bool _useTestFreeCell;
    bool _useTestLos; // Los = Line Off Sight
    bool _useTestOnlyLine;
    bool _useTestNoBorderCell;
    int _useWorldTarget;

    int _gfxId;

    QVector<c_itemProperties> _properties;
    QVector<c_effect> _useEffects;
    QVector<c_effect> _useCriticalEffects;
    QVector<c_effect> _equipEffects;

    QMap<QString,int> _bonuses;
    QList<c_carac> _list_bonuses;
    QMap<QString,QString> _constraints;
    QList<QString> _elements;
    int _number_element;    

public:
    static QMap<QString,int> mapTypeToId;
    static QMap<QString,QString> mapPositionToType;
    static QMap<QString,int> mapRarityToId;
    static QMap<QString,int> mapCaracToId;
    static QMap<QString,int> mapFamilierSpeToLvl;
    static QMap<QString,int> init_mapTypeToId();
    static QMap<QString,QString> init_mapPositionToType();
    static QMap<QString,int> init_mapRarityToId();
    static QMap<QString,int> init_mapCaracToId();
    static QMap<QString,int> ini_mapFamilierSpeToLvl();

    int getId() const;
    int getLvl() const;
    QString getName() const;
    QString getDescription() const;
    c_equipmentItemTypes getType() const;
    int getSetId() const;
    int getRarity() const;
    int getBindType() const;
    int getMinShardNumber() const;
    int getMaxShardNumber() const;
    int getApUseCost() const;
    int getMpUseCost() const;
    int getWpUseCost() const;
    int getMinRange() const;
    int getMaxRange() const;
    bool TestFreeCell() const;
    bool TestLos() const;
    bool TestOnlyLine() const;
    bool TestNoBorderCell() const;
    int useWorldTarget() const;
    int getGfxId() const;
    QVector<c_itemProperties> getProperties() const;
    QVector<c_effect> getUseEffects() const;
    QVector<c_effect> getUseCriticalEffects() const;
    QVector<c_effect> getEquipEffects() const;
    QStringList getEquipEffectsString() const;
    QStringList getUseEffectsString() const;
    QStringList getUseCriticalEffectsString() const;

    void setId(const int);
    void setLvl(const int);
    void setName(const QString);
    void setDescription(const QString);
    void setType(const c_equipmentItemTypes);
    void setSetId(const int);
    void setRarity(const int);
    void setBindType(const int);
    void setMinShardeNumber(const int);
    void setMaxShardNumber(const int);
    void setApUseCost(const int);
    void setMpUseCost(const int);
    void setWpUseCost(const int);
    void setMinRange(const int);
    void setMaxRange(const int);
    void setFreeCell(const bool);
    void setLos(const bool);
    void setOnlyLine(const bool);
    void setNoBorderCell(const bool);
    void setUseWorldTarget(const int);
    void setGfxId(const int);
    void setProperties(const QVector<c_itemProperties>);
    void setUseEffects(const QVector<c_effect>);
    void setUseCriticalEffects(const QVector<c_effect>);
    void setEquipEffets(const QVector<c_effect>);

    void initBonuses();
    QMap<QString,int> getBonuses() const;
    bool isEmpty();
    QList<QString> getElements(int number = 4) const;
    void setElements(const QList<QString> &elements);
    QMap<QString, QString> getConstraints() const;
    void setConstraints(const QMap<QString, QString> &constraints);
    int getNumber_element() const;
    void setNumber_element(int value);

    static QStringList position();
    QList<c_carac> getList_bonuses() const;
    void setList_bonuses(const QList<c_carac> &list_bonuses);
};

#endif // C_ITEM_H
