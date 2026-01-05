#include "tokenizer.h"

namespace regex_group_name {
static const char kCharacType[] = "characType";
static const char kValue[] = "value";
static const char kText[] = "text";
static const char kExpression[] = "expression";
static const char kCondition[] = "condition";
static const char kPathTrue[] = "pathTrue";
static const char kPathFalse[] = "pathFalse";
static const char kLValue[] = "lValue";
static const char kElem[] = "elem";
static const char kRest[] = "rest";
}  // namespace regex_group_name

const QRegularExpression Tokenizer::rx_charac =
    QRegularExpression(QString("(^\\[#charac (?<%1>[A-Z_]*)\\] (?<%2>.*))")
                           .arg(regex_group_name::kCharacType)
                           .arg(regex_group_name::kRest));
const QRegularExpression Tokenizer::rx_assig =
    QRegularExpression(QString("(^\\[#(?<%1>\\d)\\](?<%2>.*))")
                           .arg(regex_group_name::kValue)
                           .arg(regex_group_name::kRest));
const QRegularExpression Tokenizer::rx_word =
    QRegularExpression(QString("(?<%1>^[A-Za-zÀ-ÖØ-öø-ÿÆŒ%:\\-\\(\\)0-9 "
                               "]+)(?<%2>.*)")
                           .arg(regex_group_name::kText)
                           .arg(regex_group_name::kRest));
const QRegularExpression Tokenizer::rx_condi =
    QRegularExpression(QString("(?<%1>^\\{\\[(?<%2>\\d?)(?<%3>\\D)(?<%4>\\d)\\]\\?(?<%5>[^\\:]*)\\:"
                               "(?<%6>[^\\{]*|.*\\{.+\\}.*)\\})(?<%7>.*)")
                           .arg(regex_group_name::kExpression)
                           .arg(regex_group_name::kLValue)
                           .arg(regex_group_name::kCondition)
                           .arg(regex_group_name::kValue)
                           .arg(regex_group_name::kPathTrue)
                           .arg(regex_group_name::kPathFalse)
                           .arg(regex_group_name::kRest));
const QRegularExpression Tokenizer::rx_elem =
    QRegularExpression(QString("^\\[(?<%1>[a-zA-Z0-9]+)\\](?<%2>.*)")
                           .arg(regex_group_name::kElem)
                           .arg(regex_group_name::kRest));
const QRegularExpression Tokenizer::rx_state = QRegularExpression(".*\\[(\\d*)\\].*");
const QRegularExpression Tokenizer::rx_value =
    QRegularExpression(QString("(?<%1>^[0-9\\-]+)%? (?<%2>.*)")
                           .arg(regex_group_name::kElem)
                           .arg(regex_group_name::kRest));
const QRegularExpression Tokenizer::rx_sentence =
    QRegularExpression("([A-Za-zÀ-ÖØ-öø-ÿÆŒ\\. ]+)([0-9]*)([A-Za-zÀ-ÖØ-öø-ÿÆŒ\\. ]*)");

Token::Condition Token::toCondition(char c) {
    Condition res;
    switch (c) {
        case '>':
            res = Condition::kGreaterEqual;
            break;
        case '<':
            res = Condition::kLesser;
            break;
        case '=':
            res = Condition::kEqual;
            break;
        case '~':
            res = Condition::kExist;
            break;
        default:
            res = Condition::kNothing;
            break;
    }
    return res;
}

Token Tokenizer::tokenize(const QString string) const {
    Token token;
    auto m_charac = rx_charac.match(string);
    auto m_assig = rx_assig.match(string);
    auto m_word = rx_word.match(string);
    auto m_condi = rx_condi.match(string);
    auto m_elem = rx_elem.match(string);

    if (m_charac.hasMatch()) {
        token.type = Token::Type::kCharac;
        token.characType = m_charac.captured(regex_group_name::kCharacType);
        token.rest = m_charac.captured(regex_group_name::kRest);
    } else if (m_assig.hasMatch()) {
        token.type = Token::Type::kAssignment;
        token.value = m_assig.captured(regex_group_name::kValue).toInt();
        token.rest = m_assig.captured(regex_group_name::kRest);
    } else if (m_word.hasMatch()) {
        token.type = Token::Type::kTexte;
        token.text = m_word.captured(regex_group_name::kText);
        token.rest = m_word.captured(regex_group_name::kRest);
    } else if (m_condi.hasMatch()) {
        token.type = Token::Type::kCondition;
        token.expression = m_condi.captured(regex_group_name::kExpression);
        token.condition =
            Token::toCondition(m_condi.captured(regex_group_name::kCondition).at(0).toLatin1());
        token.value = m_condi.captured(regex_group_name::kValue).toInt();
        token.pathTrue = m_condi.captured(regex_group_name::kPathTrue);
        token.pathFalse = m_condi.captured(regex_group_name::kPathFalse);
        token.lValue = m_condi.captured(regex_group_name::kLValue);
        token.rest = m_condi.captured(regex_group_name::kRest);
    } else if (m_elem.hasMatch()) {
        token.type = Token::Type::kElement;
        token.elem = m_elem.captured(regex_group_name::kElem);
        token.rest = m_elem.captured(regex_group_name::kRest);
    } else {
        token.type = Token::Type::kNothing;
    }
    return token;
}

QString Tokenizer::formatString(const QString string, const QList<float> params, const int lvl,
                                const int stack) const {
    QString res;
    Token token = tokenize(string);
    switch (token.type) {
        case Token::Type::kNothing:
            return res;

        case Token::Type::kCharac:
            return formatString(token.rest, params, lvl, stack);

        case Token::Type::kAssignment: {
            int index = token.value;
            int value = int(params.at(index * 2 - 1) * lvl + params.at(index * 2 - 2));
            res = QString("%1").arg(value);
            return res + formatString(token.rest, params, lvl, value);
        }

        case Token::Type::kTexte:
            return token.text + formatString(token.rest, params, lvl, stack);

        case Token::Type::kCondition: {
            int l_value = stack;
            if (!token.lValue.isEmpty()) {
                l_value =
                    int(params.at(token.lValue.toInt()));  // FIX that later if there is an issue
            }
            QString branch;
            switch (token.condition) {
                case Token::Condition::kGreaterEqual:
                    branch = (stack >= token.value ? token.pathTrue : token.pathFalse);
                    break;
                case Token::Condition::kLesser:
                    branch = (stack < token.value ? token.pathTrue : token.pathFalse);
                    break;
                case Token::Condition::kEqual:
                    branch = (l_value == token.value ? token.pathTrue : token.pathFalse);
                    break;
                case Token::Condition::kExist:
                    branch = params.size() / 2 == token.value ? token.pathTrue : token.pathFalse;
                    break;
                default:
                    return res;
            }
            return formatString(branch, params, lvl, stack) +
                   formatString(token.rest, params, lvl, stack);
        }
        case Token::Type::kElement: {
            QString rest = token.rest;
            QString prefix = token.elem;
            if (token.elem.contains(QString("st"))) {
                prefix = QString("[%1]").arg(token.elem.replace("st", ""));
            }

            res = prefix + formatString(token.rest, params, lvl, stack);
        }
    }
    return res;
}

int Tokenizer::get_id_state(const QString string) const {
    QStringList capturedText;
    auto m_state = rx_state.match(string);
    if (m_state.hasMatch()) {
        return m_state.captured(1).toInt();
    }
    return 0;
}

QMap<QString, QString> Tokenizer::interpret_effect(const QString string) const {
    QStringList capturedText;
    QMap<QString, QString> res;
    auto m_value = rx_value.match(string);
    if (m_value.hasMatch()) {
        res["value"] = m_value.captured(1);
        auto m_sentence = rx_sentence.match(m_value.captured(2));
        if (m_sentence.hasMatch()) {
            QString type_effect = m_sentence.captured(1);
            QString opt_number;
            if (m_sentence.lastCapturedIndex() > 2) {
                opt_number = m_sentence.captured(2);
            }
            if ((type_effect.contains("PV") || type_effect.contains("Vie")) &&
                !type_effect.contains("Vol")) {
                res["effect"] = "Vie";
            } else if (type_effect.contains("PA")) {
                res["effect"] = "PA";
            } else if (type_effect.contains("PM")) {
                res["effect"] = "PM";
            } else if (type_effect.contains("PW")) {
                res["effect"] = "PW";
            } else if (type_effect.contains("Maîtrise Élémentaire")) {
                res["effect"] = "Maîtrise Élémentaire";
            } else if (type_effect.contains("Maîtrise Élémentaire Feu")) {
                res["effect"] = "Maîtrise Élémentaire Feu";
            } else if (type_effect.contains("Maîtrise Élémentaire Eau")) {
                res["effect"] = "Maîtrise Élémentaire Eau";
            } else if (type_effect.contains("Maîtrise Élémentaire Terre")) {
                res["effect"] = "Maîtrise Élémentaire Terre";
            } else if (type_effect.contains("Maîtrise Élémentaire Air")) {
                res["effect"] = "Maîtrise Élémentaire Air";
            } else if (type_effect.contains("Maîtrise sur")) {
                res["effect"] = QString("Maîtrise sur %1 éléments").arg(opt_number);
            } else if (type_effect.contains("Résistance Élémentaire")) {
                res["effect"] = "Résistance Élémentaire";
            } else if (type_effect.contains("Résistance Feu")) {
                res["effect"] = "Résistance Feu";
            } else if (type_effect.contains("Résistance Eau")) {
                res["effect"] = "Résistance Eau";
            } else if (type_effect.contains("Résistance Terre")) {
                res["effect"] = "Résistance Terre";
            } else if (type_effect.contains("Résistance Air")) {
                res["effect"] = "Résistance Air";
            } else if (type_effect.contains("Résistance sur")) {
                res["effect"] = QString("Résistance sur %1 éléments").arg(opt_number);
            } else if (type_effect.contains("Dommages infligés")) {
                res["effect"] = "Dommages infligés";
            } else if (type_effect.contains("Soins réalisés")) {
                res["effect"] = "Soins réalisés";
            } else if (type_effect.contains("Parade")) {
                res["effect"] = "Parade";
            } else if (type_effect.contains("Coup Critique")) {
                res["effect"] = "Coup Critique";
            } else if (type_effect.contains("Initiative")) {
                res["effect"] = "Initiative";
            } else if (type_effect.contains("Portée")) {
                res["effect"] = "Portée";
            } else if (type_effect.contains("Esquive")) {
                res["effect"] = "Esquive";
            } else if (type_effect.contains("Tacle")) {
                res["effect"] = "Tacle";
            } else if (type_effect.contains("Sagesse")) {
                res["effect"] = "Sagesse";
            } else if (type_effect.contains("Prospection")) {
                res["effect"] = "Prospection";
            } else if (type_effect.contains("Contrôle")) {
                res["effect"] = "Contrôle";
            } else if (type_effect.contains("Art du barda")) {
                res["effect"] = "Art du barda";
            } else if (type_effect.contains("Volonté")) {
                res["effect"] = "Volonté";
            } else if (type_effect.contains("Maîtrise Critique")) {
                res["effect"] = "Maîtrise Critique";
            } else if (type_effect.contains("Résistance Critique")) {
                res["effect"] = "Résistance Critique";
            } else if (type_effect.contains("Maîtrise Dos")) {
                res["effect"] = "Maîtrise Dos";
            } else if (type_effect.contains("Résistance Dos")) {
                res["effect"] = "Résistance Dos";
            } else if (type_effect.contains("Maîtrise Mêlée")) {
                res["effect"] = "Maîtrise Mêlée";
            } else if (type_effect.contains("Maîtrise Distance")) {
                res["effect"] = "Maîtrise Distance";
            } else if (type_effect.contains("Maîtrise Monocible")) {
                res["effect"] = "Maîtrise Monocible";
            } else if (type_effect.contains("Maîtrise Zone")) {
                res["effect"] = "Maîtrise Zone";
            } else if (type_effect.contains("Maîtrise Soin")) {
                res["effect"] = "Maîtrise Soin";
            } else if (type_effect.contains("Maîtrise Berserk")) {
                res["effect"] = "Maîtrise Berserk";
            } else if (type_effect.contains("Niv. aux sorts Feu")) {
                res["effect"] = "Niv. aux sorts Feu";
            } else if (type_effect.contains("Niv. aux sorts Eau")) {
                res["effect"] = "Niv. aux sorts Eau";
            } else if (type_effect.contains("Niv. aux sorts Terre")) {
                res["effect"] = "Niv. aux sorts Terre";
            } else if (type_effect.contains("Niv. aux sorts Air")) {
                res["effect"] = "Niv. aux sorts Air";
            } else if (type_effect.contains("Armure reçue")) {
                res["effect"] = "Armure reçue";
            } else if (type_effect.contains("Armure donnée")) {
                res["effect"] = "Armure donnée";
            } else {
                res["effect"] = "Nothing";
            }
        }
    }
    return res;
}
