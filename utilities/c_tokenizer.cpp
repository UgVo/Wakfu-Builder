#include "c_tokenizer.h"

c_tokenizer::c_tokenizer() {
    rx_assig = QRegExp("(^\\[#(\\d)\\](.*))");
    rx_word = QRegExp("(^[a-zA-Z-áàâäãåçéèêëíìîïñóòôöõúùûüýÿæœÁÀÂÄÃÅÇÉÈÊËÍÌÎÏÑÓÒÔÖÕÚÙÛÜÝŸÆŒ%:\\(\\)0-9 ]+)(.*)");
    rx_condi = QRegExp("(^\\{\\[(\\d?)(\\D)(\\d)\\]\\?([^\\:]*)\\:([^\\{]*|.*\\{.+\\}.*)\\})(.*)");
    rx_elem = QRegExp("^\\[([a-zA-Z0-9]+)\\](.*)");
    rx_state = QRegExp(".*\\[(\\d*)\\].*");
    rx_value = QRegExp("(^[0-9\\-]+)%? (.*)");
    rx_sentence = QRegExp("([a-zA-Z-áàâäãåçéèêëíìîïñóòôöõúùûüýÿæœÁÀÂÄÃÅÇÉÈÊËÍÌÎÏÑÓÒÔÖÕÚÙÛÜÝŸÆŒ\\. ]+)([0-9]*)([a-zA-Z-áàâäãåçéèêëíìîïñóòôöõúùûüýÿæœÁÀÂÄÃÅÇÉÈÊËÍÌÎÏÑÓÒÔÖÕÚÙÛÜÝŸÆŒ\\. ]*)");

}

QMap<QString,QString> c_tokenizer::tokenize(const QString string) const {
    QMap<QString,QString> elem;
    QStringList capturedText;
    if (!rx_assig.indexIn(string)) {
        capturedText = rx_assig.capturedTexts();
        elem.insert("type","assignment");
        elem.insert("value",capturedText.at(2));
        elem.insert("rest",capturedText.at(3));
    } else if (!rx_word.indexIn(string)) {
        capturedText = rx_word.capturedTexts();
        elem.insert("type","texte");
        elem.insert("text",capturedText.at(1));
        elem.insert("rest",capturedText.at(2));
    } else if (!rx_condi.indexIn(string)) {
        capturedText = rx_condi.capturedTexts();
        elem.insert("type","condition");
        elem.insert("expression",capturedText.at(1));
        elem.insert("rest",capturedText.at(7));
        elem.insert("operator",capturedText.at(3));
        elem.insert("value",capturedText.at(4));
        elem.insert("true",capturedText.at(5));
        elem.insert("false",capturedText.at(6));
        elem.insert("l_value",capturedText.at(2));
    } else if(!rx_elem.indexIn(string)) {
        capturedText = rx_elem.capturedTexts();
        elem.insert("type","element");
        elem.insert("elem",capturedText.at(1));
        elem.insert("rest",capturedText.at(2));

    } else {
        elem.insert("type","nothing");
    }
    return elem;
}

QString c_tokenizer::formatString(const QString string, const QList<float> params, const int lvl, const int stack) const {
    QString res;
    QMap<QString,QString> token = tokenize(string);
    if (!token.value(QString("type")).compare(QString("nothing"))) {
        return res;
    } else if (!token.value(QString("type")).compare(QString("assignment"))) {
        int index = token.value("value").toInt();
        int value = int(params.at(index*2-1)*lvl + params.at(index*2-2));
        res = QString("%1").arg(value);
        return res + formatString(token.value("rest"),params,lvl,value);
    } else if (!token.value(QString("type")).compare(QString("texte"))) {
        res = token.value("text");
        return res + formatString(token.value("rest"),params,lvl,stack);
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
            l_value = int(params.at(l_value_str.toInt())); //FIX that later if there is an issue
        }
        switch (operator_str.at(0).toLatin1()) {
            case '>':
                if (stack >= value_str.toInt()) {
                    res = formatString(true_str,params,lvl,stack) + formatString(rest,params,lvl,stack);
                } else {
                    res = formatString(false_str,params,lvl,stack) + formatString(rest,params,lvl,stack);
                }
                break;
            case '<':
                if (stack < value_str.toInt()) {
                    res = formatString(true_str,params,lvl,stack) + formatString(rest,params,lvl,stack);
                } else {
                    res = formatString(false_str,params,lvl,stack) + formatString(rest,params,lvl,stack);
                }
            break;
            case '=':
                if (l_value == value_str.toInt()) {
                    res = formatString(true_str,params,lvl,stack) + formatString(rest,params,lvl,stack);
                } else {
                    res = formatString(false_str,params,lvl,stack) + formatString(rest,params,lvl,stack);
                }
                break;
            case '~':
                if (params.size()/2 == value_str.toInt()) {
                    res = formatString(true_str,params,lvl,stack) + formatString(rest,params,lvl,stack);
                } else {
                    res = formatString(false_str,params,lvl,stack) + formatString(rest,params,lvl,stack);
                }
                break;
            default:
                break;
        }
    } else if (!token.value(QString("type")).compare(QString("element"))) {
        QString rest = token.value(QString("rest"));
        if (!token.value(QString("elem")).compare(QString("el1"))) {
            res = "Feu" + formatString(rest,params,lvl,stack);
        } else if (!token.value(QString("elem")).compare(QString("el2"))) {
            res = "Eau" + formatString(rest,params,lvl,stack);
        } else if (!token.value(QString("elem")).compare(QString("el3"))) {
            res = "Terre" + formatString(rest,params,lvl,stack);
        } else if (!token.value(QString("elem")).compare(QString("el4"))) {
            res = "Air" + formatString(rest,params,lvl,stack);
        } else if (!token.value(QString("elem")).compare(QString("el5"))) {
            res = "Stasis" + formatString(rest,params,lvl,stack);
        } else if (!token.value(QString("elem")).compare(QString("el6"))) {
            res = "Lumière" + formatString(rest,params,lvl,stack);
        } else if (!token.value(QString("elem")).compare(QString("ally"))) {
            res = "ally" + formatString(rest,params,lvl,stack);
        } else if (token.value(QString("elem")).contains(QString("st"))) {
            QString id_state = token.value(QString("elem"));
            res = QString("[%1]").arg(id_state.replace("st","")) + formatString(rest,params,lvl,stack);
        }
    }
    return res;
}

int c_tokenizer::get_id_state(const QString string) const {
    QStringList capturedText;
    if (!rx_state.indexIn(string)) {
        capturedText = rx_state.capturedTexts();
        return capturedText.at(1).toInt();
    }
    return 0;
}

QMap<QString,QString> c_tokenizer::interpret_effect(const QString string) const {
    QStringList capturedText;
    QMap<QString,QString> res;
    if (!rx_value.indexIn(string)) {
        capturedText = rx_value.capturedTexts();
        res["value"] = capturedText.at(1);
        if (!rx_sentence.indexIn(capturedText.at(2))) {
            QString type_effect = rx_sentence.capturedTexts().at(1);
            QString opt_number;
            if (rx_sentence.capturedTexts().size() > 2) {
                opt_number = rx_sentence.capturedTexts().at(2);
            }
            if ((type_effect.contains("PV") || type_effect.contains("Vie")) && !type_effect.contains("Vol")) {
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
            } else {
                res["effect"] = "Nothing";
            }
        }
    }
    return res;
}


