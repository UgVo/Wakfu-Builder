#ifndef C_DBMANAGER_H
#define C_DBMANAGER_H

#include "c_effect.h"
#include "c_action.h"
#include "c_itemproperties.h"
#include "c_equipmentitemtypes.h"
#include "c_item.h"
#include "c_state.h"
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QList>
#include <QStringList>
#include <QElapsedTimer>

class c_datamanager;

class c_dbmanager
{
public:
    c_dbmanager(c_datamanager *manager);
    ~c_dbmanager();

    bool add_effect(c_effect new_effect);
    c_effect get_effect(const int id);

    bool add_action(c_action new_action);
    c_action get_action(const int id);  // TODO !

    bool add_itemProperty(c_itemProperties new_property);
    c_itemProperties get_itemProperty(const int id);

    bool add_equipmentItemType(c_equipmentItemTypes new_type);
    c_equipmentItemTypes get_equipmentItemType(const int id);

    bool add_equipmentPosition(QString name, int id);
    QString get_equipmentPosition(int id);
    QStringList get_AllEquipementPosition();
    int get_equipmentPositionId(QString name);

    bool add_relation_equipementType_Position(int equipementTypeId, int positionId);
    bool add_relation_equipementType_PositionDisable(int equipementTypeId, int positionId);

    bool add_item(c_item item);
    c_item get_item(int id);
    bool add_relation_item_property(int id_Item, int id_propertie);
    bool add_relation_item_useEffect(int id_Item, int id_effect);
    bool add_relation_item_useCriEffect(int id_Item, int id_effect);
    bool add_relation_item_equipeEffect(int id_Item, int id_effect);

    QList<int> getImagesList();
    QList<int> getItemListId();

    QList<c_item> getAllItem();

    bool add_state(c_state state);
    c_state get_state(int id);

    QList<int> getid_item_from_actions(QList<QString> caract_name, QList<int> rarities, QList<int> types, QList<int> bondaries = {1,200}, QString name = QString(), bool final = false, QList<bool> condi = QList<bool>());
    QList<int> getid_item_from_actions_sorted(QList<QString> carac_effect, QList<int> rarities, QList<int> types, QList<int> bondaries = {1,200}, QString name = QString(), bool final = false, QList<bool> condi = QList<bool>());
    QList<c_item> getItems(QList<int> ids);
    c_item getItemFromQueryLite(QSqlQuery record);

    QVector<c_effect> getUseEffectFromItemId(int id);
    QVector<c_effect> getEquipEffectFromItemId(int id);

    int add_save_builder(QString json, QString name, int lvl);
    int update_save_builder(QString json, int id, QString name, int lvl);

    QSqlDatabase getDb() const;

    bool add_carac(c_carac carac);
    c_carac get_carac(int id);
    bool add_relation_item_carac(int id_item, int id_carac);

    QString generateCombiQuery_action(QList<bool> condi);
    QString generateCombiQuery_carac(QList<bool> condi);
    QString prepareQuery_simple(QList<QString> action_ids, QList<int> rarities, QList<int> types, QList<int> bondaries = {1,200}, QString name = QString(), bool final = false);
    QString prepareQuery_condi(QList<QString> caract_name, QList<int> rarities, QList<int> types, QList<int> bondaries = {1,200}, QString name = QString(), bool final = false, QList<bool> condi = QList<bool>());


private:
    QSqlDatabase m_db;
    QStringList PositionTypeList;
};

#endif // C_DBMANAGER_H
