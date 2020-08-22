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
    int getId() const;
    int getParentId() const;
    QStringList getEquipementPositions() const;
    QStringList getEquipementDisablePositions() const;
    bool isRecyclable() const;
    bool isVisibleInAnimation() const;
    QString getTitle() const;

    void setId(const int);
    void setParentId(const int);
    void setEquipementPositions(const QStringList);
    void setEquipementDisablePositions(const QStringList);
    void setRecyclable(const bool);
    void setVisibleInAnimation(const bool);
    void setTitle(const QString);

};

#endif // C_EQUIPMENTITEMTYPES_H
