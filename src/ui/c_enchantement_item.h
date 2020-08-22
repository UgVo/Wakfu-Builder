#ifndef C_ENCHANTEMENT_ITEM_H
#define C_ENCHANTEMENT_ITEM_H

#include <QWidget>
#include <QToolButton>
#include "utilities/c_enchantement_chasse.h"
#include "utilities/c_enchantement_effect.h"
#include "ui.h"
#include "c_tool_button.h"

namespace Ui {
class c_enchantement_item;
}

class c_enchantement_item : public QWidget
{
    Q_OBJECT

public:
    explicit c_enchantement_item(QWidget *parent = nullptr, QString emplacement = QString());
    ~c_enchantement_item();

    void updateView();
    void setButtonStyle(QToolButton *bt);

    QString emplacement() const;

    QList<c_enchantement_chasse> chasse_list() const;
    void setChasse_list(const QList<c_enchantement_chasse> &chasse_list);

    int level() const;

public slots:
    void slot_highlightPosition(bool flag);
    void slot_positionClicked();
    void slot_slotClicked();
    void slot_slotRightClicked();
    void setLevel(int level);
    QMap<QString, int> computeBonus();

signals:
    void positionSelected(QString position);
    void enchantSetUpdated();

private:
    Ui::c_enchantement_item *ui;
    QWidget* _parent;
    QString _emplacement;
    QList<c_enchantement_chasse> _chasse_list;
    QList<c_tool_button*> _tool_buttons;
    int _level;
    bool _block;

};

#endif // C_ENCHANTEMENT_ITEM_H
