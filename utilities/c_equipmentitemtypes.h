#ifndef C_EQUIPMENTITEMTYPES_H
#define C_EQUIPMENTITEMTYPES_H

#include <QStringList>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

class c_equipmentItemTypes
{
public:
    c_equipmentItemTypes(int id = 0, int parentId = 0,
                         QStringList equipementPositions = QStringList(),
                         QStringList equipementDisablePositions = QStringList(),
                         bool recyclable = true, bool visibleInAnimation = true,
                         QString title = QString());
    c_equipmentItemTypes(QJsonObject object);

private:
    int id;
    int parentId;
    QStringList equipementPositions;
    QStringList equipmentDisabledPositions;
    bool recyclable;
    bool visibleInAnimation;
    QString title;

public:
    int getId();
    int getParentId();
    QStringList getEquipementPositions();
    QStringList getEquipementDisablePositions();
    bool isRecyclable();
    bool isVisibleInAnimation();
    QString getTitle();

    void setId(int);
    void setParentId(int);
    void setEquipementPositions(QStringList);
    void setEquipementDisablePositions(QStringList);
    void setRecyclable(bool);
    void setVisibleInAnimation(bool);
    void setTitle(QString);

};

#endif // C_EQUIPMENTITEMTYPES_H
