#ifndef C_TOKENIZER_H
#define C_TOKENIZER_H

#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QDebug>
#include <QMap>

class c_tokenizer
{
public:
    c_tokenizer();
    QString formatString(const QString string,const QList<float> params,const int lvl,const int stack) const;
    QMap<QString,QString> tokenize(const QString string) const;
    int get_id_state(const QString string) const;
    QMap<QString,QString> interpret_effect(const QString string) const;

private:
    QRegExp rx_assig;
    QRegExp rx_word;
    QRegExp rx_condi;
    QRegExp rx_elem;
    QRegExp rx_state;
    QRegExp rx_value;
    QRegExp rx_sentence;
};

#endif // C_TOKENIZER_H
