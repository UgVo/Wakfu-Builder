#ifndef C_ITEMPROPERTIES_H
#define C_ITEMPROPERTIES_H

#include <QString>
#include <QJsonObject>

class c_itemProperties
{
public:
    c_itemProperties(int id = 0, QString name = QString(), QString description = QString());
    c_itemProperties(QJsonObject actionObject);

    int getId();
    QString getName();
    QString getDescription();
    void setId(int id);
    void setName(QString name);
    void setDescription(QString description);

private:
    int id;
    QString name;
    QString description;
};

#endif // C_ITEMPROPERTIES_H
