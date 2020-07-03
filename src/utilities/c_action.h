#ifndef C_ACTION_H
#define C_ACTION_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include "utilities/c_tokenizer.h"

class c_action
{
public:
    c_action(int id = 0, QString effect = QString(), QString description = QString());
    c_action(QJsonObject actionObject);

private:
    int _id;
    QString _effect;
    QString _description;
    c_tokenizer tokenizer;

public:
    void setId(const int id) ;
    void setEffect(const QString effect);
    void setDescription(const QString description);

    int getId() const;
    QString getEffect() const;
    QString getDescription() const;

    QString getText(const QList<float>, const int) const;
};

#endif // C_ACTION_H
