#ifndef C_ENCHANTEMENT_DISPLAY_H
#define C_ENCHANTEMENT_DISPLAY_H

#include <QWidget>
#include "utilities/c_enchantement_effect.h"
#include "ui/c_enchantement_item.h"
#include "c_enchantement_lite.h"
#include "utilities/c_dbmanager.h"
#include "ui.h"
#include "utilities/c_build.h"

namespace Ui {
class c_enchantement_display;
}

class c_enchantement_display : public QWidget
{
    Q_OBJECT

public:
    explicit c_enchantement_display(QWidget *parent = nullptr, c_dbmanager* manager = nullptr,c_build* build = nullptr);
    ~c_enchantement_display();

    c_enchantement_effect selected_effect() const;

    QMap<QString, c_enchantement_item *> getItem_slots_map() const;
    void setItem_slots_map(const QMap<QString, c_enchantement_item *> &value);

    void setChasses(const QMap<QString,QList<c_enchantement_chasse>> map);

private:
    Ui::c_enchantement_display *ui;
    c_dbmanager *_manager;
    c_build * _build;
    QMap<QString,c_enchantement_item*> item_slots_map;
    QMap<int,c_enchantement_lite*> effect_map;
    c_enchantement_effect _selected_effect;

public slots:
    void slot_effectClicked(int id);
    void slot_positionSelected(QString position);
    void slot_setLevel(int level);
    void slot_buildUpdated();
    void slot_enchantSetUpdated();
};

#endif // C_ENCHANTEMENT_DISPLAY_H
