#ifndef C_TOKENIZER_H
#define C_TOKENIZER_H

#include <QDebug>
#include <QMap>
#include <QRegularExpression>
#include <QString>
#include <QStringList>

class c_tokenizer {
   public:
    c_tokenizer();
    QString formatString(const QString string, const QList<float> params, const int lvl,
                         const int stack) const;
    QMap<QString, QString> tokenize(const QString string) const;
    int get_id_state(const QString string) const;
    QMap<QString, QString> interpret_effect(const QString string) const;

   private:
    QRegularExpression rx_assig;
    QRegularExpression rx_word;
    QRegularExpression rx_condi;
    QRegularExpression rx_elem;
    QRegularExpression rx_state;
    QRegularExpression rx_value;
    QRegularExpression rx_sentence;
};

#endif  // C_TOKENIZER_H
