#include "c_tokenizer.h"

c_tokenizer::c_tokenizer() {
    rx_assig = QRegularExpression("(^\\[#charac ([A-Z_]*)\\] \\[#(\\d)\\](.*))");
    rx_word = QRegularExpression(
        "(^[a-zA-Z-áàâäãåçéèêëíìîïñóòôöõúùûüýÿæœÁÀÂÄÃÅÇÉÈÊËÍÌÎÏÑÓÒÔÖÕÚÙÛÜÝŸÆŒ%:\\(\\)0-9 ]+)(.*)");
    rx_condi = QRegularExpression(
        "(^\\{\\[(\\d?)(\\D)(\\d)\\]\\?([^\\:]*)\\:([^\\{]*|.*\\{.+\\}.*)\\})(.*)");
    rx_elem = QRegularExpression("^\\[([a-zA-Z0-9]+)\\](.*)");
    rx_state = QRegularExpression(".*\\[(\\d*)\\].*");
    rx_value = QRegularExpression("(^[0-9\\-]+)%? (.*)");
    rx_sentence = QRegularExpression(
        "([a-zA-Z-áàâäãåçéèêëíìîïñóòôöõúùûüýÿæœÁÀÂÄÃÅÇÉÈÊËÍÌÎÏÑÓÒÔÖÕÚÙÛÜÝŸÆŒ\\. "
        "]+)([0-9]*)([a-zA-Z-áàâäãåçéèêëíìîïñóòôöõúùûüýÿæœÁÀÂÄÃÅÇÉÈÊËÍÌÎÏÑÓÒÔÖÕÚÙÛÜÝŸÆŒ\\. ]*)");
}

QMap<QString, QString> c_tokenizer::tokenize(const QString string) const {
    QMap<QString, QString> elem;
    QStringList capturedText;
    auto m_assig = rx_assig.match(string);
    auto m_word = rx_word.match(string);
    auto m_condi = rx_condi.match(string);
    auto m_elem = rx_elem.match(string);

    if (m_assig.hasMatch()) {
        elem.insert("type", "assignment");
        elem.insert("charac_type", m_assig.captured(2));
        elem.insert("value", m_assig.captured(3));
        elem.insert("rest", m_assig.captured(4));
    } else if (m_word.hasMatch()) {
        elem.insert("type", "texte");
        elem.insert("text", m_word.captured(1));
        elem.insert("rest", m_word.captured(2));
    } else if (m_condi.hasMatch()) {
        elem.insert("type", "condition");
        elem.insert("expression", m_condi.captured(1));
        elem.insert("rest", m_condi.captured(7));
        elem.insert("operator", m_condi.captured(3));
        elem.insert("value", m_condi.captured(4));
        elem.insert("true", m_condi.captured(5));
        elem.insert("false", m_condi.captured(6));
        elem.insert("l_value", m_condi.captured(2));
    } else if (m_elem.hasMatch()) {
        elem.insert("type", "element");
        elem.insert("elem", m_elem.captured(1));
        elem.insert("rest", m_elem.captured(2));

    } else {
        elem.insert("type", "nothing");
    }
    return elem;
}

QString c_tokenizer::formatString(const QString string, const QList<float> params, const int lvl,
                                  const int stack) const {
    QString res;
    QMap<QString, QString> token = tokenize(string);
    if (!token.value(QString("type")).compare(QString("nothing"))) {
        return res;
    } else if (!token.value(QString("type")).compare(QString("assignment"))) {
        int index = token.value("value").toInt();
        int value = int(params.at(index * 2 - 1) * lvl + params.at(index * 2 - 2));
        res = QString("%1").arg(value);
        return res + formatString(token.value("rest"), params, lvl, value);
    } else if (!token.value(QString("type")).compare(QString("texte"))) {
        res = token.value("text");
        return res + formatString(token.value("rest"), params, lvl, stack);
    } else if (!token.value(QString("type")).compare(QString("condition"))) {
        QString operator_str = token.value(QString("operator"));
        QString value_str = token.value(QString("value"));
        QString false_str = token.value(QString("false"));
        QString true_str = token.value(QString("true"));
        QString initial = token.value(QString("expression"));
        QString rest = token.value(QString("rest"));
        QString l_value_str = token.value(QString("l_value"));
        int l_value = stack;
        if (!l_value_str.isEmpty()) {
            l_value = int(params.at(l_value_str.toInt()));  // FIX that later if there is an issue
        }
        switch (operator_str.at(0).toLatin1()) {
            case '>':
                if (stack >= value_str.toInt()) {
                    res = formatString(true_str, params, lvl, stack) +
                          formatString(rest, params, lvl, stack);
                } else {
                    res = formatString(false_str, params, lvl, stack) +
                          formatString(rest, params, lvl, stack);
                }
                break;
            case '<':
                if (stack < value_str.toInt()) {
                    res = formatString(true_str, params, lvl, stack) +
                          formatString(rest, params, lvl, stack);
                } else {
                    res = formatString(false_str, params, lvl, stack) +
                          formatString(rest, params, lvl, stack);
                }
                break;
            case '=':
                if (l_value == value_str.toInt()) {
                    res = formatString(true_str, params, lvl, stack) +
                          formatString(rest, params, lvl, stack);
                } else {
                    res = formatString(false_str, params, lvl, stack) +
                          formatString(rest, params, lvl, stack);
                }
                break;
            case '~':
                if (params.size() / 2 == value_str.toInt()) {
                    res = formatString(true_str, params, lvl, stack) +
                          formatString(rest, params, lvl, stack);
                } else {
                    res = formatString(false_str, params, lvl, stack) +
                          formatString(rest, params, lvl, stack);
                }
                break;
            default:
                break;
        }
    } else if (!token.value(QString("type")).compare(QString("element"))) {
        QString rest = token.value(QString("rest"));
        if (!token.value(QString("elem")).compare(QString("el1"))) {
            res = "Feu" + formatString(rest, params, lvl, stack);
        } else if (!token.value(QString("elem")).compare(QString("el2"))) {
            res = "Eau" + formatString(rest, params, lvl, stack);
        } else if (!token.value(QString("elem")).compare(QString("el3"))) {
            res = "Terre" + formatString(rest, params, lvl, stack);
        } else if (!token.value(QString("elem")).compare(QString("el4"))) {
            res = "Air" + formatString(rest, params, lvl, stack);
        } else if (!token.value(QString("elem")).compare(QString("el5"))) {
            res = "Stasis" + formatString(rest, params, lvl, stack);
        } else if (!token.value(QString("elem")).compare(QString("el6"))) {
            res = "Lumière" + formatString(rest, params, lvl, stack);
        } else if (!token.value(QString("elem")).compare(QString("ally"))) {
            res = "ally" + formatString(rest, params, lvl, stack);
        } else if (token.value(QString("elem")).contains(QString("st"))) {
            QString id_state = token.value(QString("elem"));
            res = QString("[%1]").arg(id_state.replace("st", "")) +
                  formatString(rest, params, lvl, stack);
        }
    }
    return res;
}

int c_tokenizer::get_id_state(const QString string) const {
    QStringList capturedText;
    auto m_state = rx_state.match(string);
    if (m_state.hasMatch()) {
        return m_state.captured(1).toInt();
    }
    return 0;
}

QMap<QString, QString> c_tokenizer::interpret_effect(const QString string) const {
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
