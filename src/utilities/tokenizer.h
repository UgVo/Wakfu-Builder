#ifndef WAKFU_BUILDER_UTILITIES_TOKENIZER_H
#define WAKFU_BUILDER_UTILITIES_TOKENIZER_H

#include <QMap>
#include <QRegularExpression>
#include <QString>

struct Token {
    enum class Type { kCharac, kAssignment, kTexte, kCondition, kElement, kNothing };
    enum class Condition { kGreaterEqual, kLesser, kEqual, kExist, kNothing };

    static Condition toCondition(char c);

    Type type = Type::kNothing;
    Condition condition;
    int value;
    QString lValue;
    QString characType;
    QString rest;
    QString text;
    QString expression;
    QString pathTrue;
    QString pathFalse;
    QString elem;
};

class Tokenizer {
   public:
    Tokenizer() = default;
    QString formatString(const QString string, const QList<float> params, const int lvl,
                         const int stack) const;
    Token tokenize(const QString string) const;
    int get_id_state(const QString string) const;
    QMap<QString, QString> interpret_effect(const QString string) const;

   private:
    static const QRegularExpression rx_charac;
    static const QRegularExpression rx_assig;
    static const QRegularExpression rx_word;
    static const QRegularExpression rx_condi;
    static const QRegularExpression rx_elem;
    static const QRegularExpression rx_state;
    static const QRegularExpression rx_value;
    static const QRegularExpression rx_sentence;
};

#endif  // WAKFU_BUILDER_UTILITIES_TOKENIZER_H
