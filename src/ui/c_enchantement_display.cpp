#include "c_enchantement_display.h"
#include "ui_c_enchantement_display.h"

c_enchantement_display::c_enchantement_display(QWidget *parent, c_dbmanager* manager, c_build* build)  :
    QWidget(parent), ui(new Ui::c_enchantement_display), _manager(manager), _build(build)
{
    ui->setupUi(this);
    QList<c_enchantement_effect> res = _manager->get_enchantement_effects();
    foreach(c_enchantement_effect effect, res) {
        qDebug() << "---------------------------" << effect.effect() << "---------------------";
        qDebug() << effect.valuePerLvl();
        effect_map.insert(effect.id(),new c_enchantement_lite(this,effect));
        QObject::connect(effect_map.last(),&c_enchantement_lite::clicked,this,&c_enchantement_display::slot_effectClicked);
        switch (effect.color()) {
            case 1:
                ui->layout_rouge->addWidget(effect_map.last());
                break;
            case 2:
                ui->layout_vert->addWidget(effect_map.last());
                break;
            case 3:
                ui->layout_bleu->addWidget(effect_map.last());
                break;
        }
    }
    item_slots_map.clear();
    item_slots_map.insertMulti("HEAD",new c_enchantement_item(this,"HEAD"));
    ui->layout_slots->insertWidget(1,item_slots_map["HEAD"]);
    item_slots_map.insertMulti("NECK",new c_enchantement_item(this,"NECK"));
    ui->layout_slots->insertWidget(2,item_slots_map["NECK"]);
    item_slots_map.insertMulti("BACK",new c_enchantement_item(this,"BACK"));
    ui->layout_slots->insertWidget(3,item_slots_map["BACK"]);
    item_slots_map.insertMulti("SHOULDERS",new c_enchantement_item(this,"SHOULDERS"));
    ui->layout_slots->insertWidget(4,item_slots_map["SHOULDERS"]);
    item_slots_map.insertMulti("CHEST",new c_enchantement_item(this,"CHEST"));
    ui->layout_slots->insertWidget(5,item_slots_map["CHEST"]);
    item_slots_map.insertMulti("BELT",new c_enchantement_item(this,"BELT"));
    ui->layout_slots->insertWidget(6,item_slots_map["BELT"]);
    item_slots_map.insertMulti("LEFT_HAND",new c_enchantement_item(this,"LEFT_HAND"));
    ui->layout_slots->insertWidget(7,item_slots_map["LEFT_HAND"]);
    item_slots_map.insertMulti("RIGHT_HAND",new c_enchantement_item(this,"RIGHT_HAND"));
    ui->layout_slots->insertWidget(8,item_slots_map["RIGHT_HAND"]);
    item_slots_map.insertMulti("LEGS",new c_enchantement_item(this,"LEGS"));
    ui->layout_slots->insertWidget(9,item_slots_map["LEGS"]);
    item_slots_map.insertMulti("FIRST_WEAPON",new c_enchantement_item(this,"FIRST_WEAPON"));
    ui->layout_slots->insertWidget(10,item_slots_map["FIRST_WEAPON"]);

    QObject::connect(build,&c_build::updated,this,&c_enchantement_display::slot_buildUpdated);

    foreach (c_enchantement_item* item, item_slots_map) {
        QObject::connect(item,&c_enchantement_item::positionSelected,this,&c_enchantement_display::slot_positionSelected);
        QObject::connect(item,&c_enchantement_item::enchantSetUpdated,this,&c_enchantement_display::slot_enchantSetUpdated);
    }
}

c_enchantement_display::~c_enchantement_display() {
    delete ui;
}

c_enchantement_effect c_enchantement_display::selected_effect() const
{
    return _selected_effect;
}

QMap<QString, c_enchantement_item *> c_enchantement_display::getItem_slots_map() const
{
    return item_slots_map;
}

void c_enchantement_display::setItem_slots_map(const QMap<QString, c_enchantement_item *> &value)
{
    item_slots_map = value;
}

void c_enchantement_display::setChasses(const QMap<QString, QList<c_enchantement_chasse> > map) {
    foreach (QString key, map.keys()) {
        item_slots_map[key]->setChasse_list(map[key]);
    }
    slot_enchantSetUpdated();
}

void c_enchantement_display::slot_effectClicked(int id) {
    foreach (c_enchantement_lite* effect, effect_map) {
        if (id != effect->id()) {
            effect->slot_highLight(false);
        }
    }
    _selected_effect = effect_map[id]->effect();
    QList<QString> position_list = effect_map[id]->effect().bonus();
    foreach (c_enchantement_item* item, item_slots_map) {
        if (position_list.contains(item->emplacement())) {
            item->slot_highlightPosition(true);
        } else {
            item->slot_highlightPosition(false);
        }
    }
}

void c_enchantement_display::slot_positionSelected(QString position) {
    foreach (c_enchantement_lite* lite, effect_map) {
        QList<QString> list = lite->effect().bonus();
        if (list.contains(position)) {
            lite->slot_highLight(true);
        } else {
            lite->slot_highLight(false);
        }
    }
    foreach (c_enchantement_item* item, item_slots_map) {
            item->slot_highlightPosition(false);
    }
}

void c_enchantement_display::slot_setLevel(int level) {
    foreach (c_enchantement_item* item, item_slots_map) {
        item->setLevel(level);
    }
}

void c_enchantement_display::slot_buildUpdated() {
    QMap<QString,c_item> equipment = _build->getEquipment();
    int lvl = _build->getLvl();
    foreach (QString key, item_slots_map.keys()) {
        if (equipment[key].isEmpty()) {
            item_slots_map[key]->setLevel(lvl);
        } else {
            item_slots_map[key]->setLevel(equipment[key].getLvl());
        }
    }
}

void c_enchantement_display::slot_enchantSetUpdated() {
     QMap<QString,int> bonus;
     foreach (c_enchantement_item* item, item_slots_map) {
         QMap<QString,int> item_bonus = item->computeBonus();
         foreach (QString key, item_bonus.keys()) {
             bonus[key] += item_bonus[key];
         }
     }
     qDebug() << bonus;
     _build->setBonus_enchant(bonus);
}
