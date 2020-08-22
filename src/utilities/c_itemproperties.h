#ifndef C_ITEMPROPERTIES_H
#define C_ITEMPROPERTIES_H

#include <QString>
#include <QJsonObject>

class c_itemProperties
{
public:
    c_itemProperties(int id = 0, QString name = QString(), QString description = QString());
    c_itemProperties(QJsonObject actionObject);

    int getId() const;
    QString getName() const;
    QString getDescription() const;
    void setId(const int id);
    void setName(const QString name);
    void setDescription(const QString description);

private:
    int id;
    QString name;
    QString description;
};

#endif // C_ITEMPROPERTIES_H
