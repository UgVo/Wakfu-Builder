#ifndef C_STATE_H
#define C_STATE_H

#include <QString>
#include <QJsonObject>

class c_state
{
public:
    c_state(int id = -1, QString name = QString(), QString description = QString());
    c_state(QJsonObject state);

    int get_id() const;
    QString get_name() const;
    QString get_description()const;

    void set_id(int id);
    void set_name(QString name);
    void set_description(QString description);

private:
    int _id;
    QString _name;
    QString _description;
};

#endif // C_STATE_H
