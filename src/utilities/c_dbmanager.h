#ifndef C_DBMANAGER_H
#define C_DBMANAGER_H

#include "c_effect.h"
#include "c_action.h"
#include "c_itemproperties.h"
#include "c_equipmentitemtypes.h"
#include "c_item.h"
#include "c_state.h"
#include "c_enchantement_effect.h"
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QList>
#include <QStringList>
#include <QElapsedTimer>
#include <QWidget>

class c_datamanager;

class c_dbmanager : public QWidget
{
    Q_OBJECT
public:
    c_dbmanager(c_datamanager *manager, QWidget *parent = nullptr);
    ~c_dbmanager();

    bool connect(QString password = QString());

    bool add_effect(const c_effect new_effect);
    c_effect get_effect(const int id) const;

    bool add_action(const c_action new_action);
    c_action get_action(const int id) const;  // TODO !

    bool add_itemProperty(const c_itemProperties new_property);
    c_itemProperties get_itemProperty(const int id) const;

    bool add_equipmentItemType(const c_equipmentItemTypes new_type);
    c_equipmentItemTypes get_equipmentItemType(const int id) const;

    bool add_equipmentPosition(const QString name, int id);
    QString get_equipmentPosition(int id) const;
    QStringList get_AllEquipementPosition() const;
    int get_equipmentPositionId(const QString name) const;

    bool add_relation_equipementType_Position(const int equipementTypeId,const int positionId);
    bool add_relation_equipementType_PositionDisable(const int equipementTypeId, const int positionId);

    bool add_item(const c_item item);
    c_item get_item(const int id) const;
    bool add_relation_item_property(const int id_Item, const int id_propertie);
    bool add_relation_item_useEffect(const int id_Item, const int id_effect);
    bool add_relation_item_useCriEffect(const int id_Item, const int id_effect);
    bool add_relation_item_equipeEffect(const int id_Item, const int id_effect);

    QList<int> getImagesList() const;
    QList<int> getItemListId() const;

    QList<c_item> getAllItem() const;

    bool add_state(const c_state state);
    c_state get_state(const int id) const;

    QList<int> getid_item_from_actions(const QList<QString> caract_name, const QList<int> rarities, const QList<int> types, const QList<int> bondaries = {1,200}, const QString name = QString(), const bool final = false, const QList<bool> condi = QList<bool>()) const;
    QList<int> getid_item_from_actions_sorted(const QList<QString> carac_effect, const QList<int> rarities, const QList<int> types, const QList<int> bondaries = {1,200}, const QString name = QString(), const bool final = false, const QList<bool> condi = QList<bool>()) const;
    QList<c_item> getItems(const QList<int> ids) const;
    c_item getItemFromQueryLite(const QSqlQuery record) const;

    QVector<c_effect> getUseEffectFromItemId(const int id) const;
    QVector<c_effect> getEquipEffectFromItemId(const int id) const;

    int add_save_builder(const QString json, const QString name, const int lvl);
    int update_save_builder(const QString json, const int id, const QString name, const int lvl);
    int remove_builder(const int id);

    QSqlDatabase getDb() const;

    bool add_carac(const c_carac carac);
    c_carac get_carac(const int id) const;
    bool add_relation_item_carac(const int id_item, const int id_carac);

    QString generateCombiQuery_action(const QList<bool> condi) const;
    QString generateCombiQuery_carac(const QList<bool> condi) const;
    QString prepareQuery_simple(const QList<QString> action_ids, const QList<int> rarities, const QList<int> types, const QList<int> bondaries = {1,200}, const QString name = QString(), const bool final = false) const;
    QString prepareQuery_condi(const QList<QString> caract_name, const QList<int> rarities, const QList<int> types, const QList<int> bondaries = {1,200}, const QString name = QString(), const bool final = false, const QList<bool> condi = QList<bool>()) const;

    bool setFinal(const QList<int> isFinalList);

    void empty_database();
    void check_structure();
    void debug_check_table_structure(const QString name, const int size);
    int get_number_column(const QString table) const;

    bool add_enchantement_effect(const c_enchantement_effect effect);
    QList<c_enchantement_effect> get_enchantement_effects() const;

    c_enchantement_effect get_enchantement_effect(const QString effect) const;

private:
    QSqlDatabase m_db;
    QStringList PositionTypeList;

signals:
    void signal_connection_status(bool);
    void signal_new_save();
};

#endif // C_DBMANAGER_H
