#include "c_dbmanager.h"
#include "c_datamanager.h"

c_dbmanager::c_dbmanager(c_datamanager *manager, QWidget *parent) : QWidget(parent){
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("localhost");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setDatabaseName("postgres");
    m_db.setUserName("wakfu_builder");
    m_db.setPassword(manager->getPassword());
}

c_dbmanager::~c_dbmanager() {
    QString database_name = m_db.connectionName();
    m_db.close();
    QSqlDatabase::removeDatabase(database_name);
}

bool c_dbmanager::connect(QString password) {
    if (!password.isEmpty()) {
        m_db.setPassword(password);
    }
    bool flag = m_db.open();
    qDebug() << "Openning database :" << flag;
    emit signal_connection_status(flag);
    check_structure();
    return flag;
}

bool c_dbmanager::add_effect(c_effect new_effect) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.effect (id,actionId,areaShape,areaSize,params,description) "
                  "VALUES (:id, :actionId, :areaShape, :areaSize, :params, :description)");
    query.bindValue(":id", new_effect.getId());
    query.bindValue(":actionId", new_effect.getAction().getId());
    query.bindValue(":areaShape", new_effect.getAreaShape());
    query.bindValue(":areaSize", new_effect.getAreaSize_string());
    query.bindValue(":params", new_effect.getParams_string());
    query.bindValue(":description",new_effect.getDescription());
    bool flag = query.exec();
    return flag;
}

c_effect c_dbmanager::get_effect(const int id) {
    QSqlQuery query(m_db);
    c_effect new_effect(this);
    query.prepare("SELECT * FROM wakfu_builder.effect "
                  "WHERE id = :id");
    query.bindValue(":id",id);
    if (query.exec()) {
        int id = query.record().indexOf("id");
        int idAction = query.record().indexOf("actionId");
        int idShape = query.record().indexOf("areaShape");
        int idSize = query.record().indexOf("areaSize");
        int idParams = query.record().indexOf("params");
        int idDescr = query.record().indexOf("description");
        while (query.next()) {
            new_effect.setId(query.value(id).toInt());
            new_effect.setAreaShape(query.value(idShape).toInt());
            new_effect.setDescrition(query.value(idDescr).toString());
            QString string_Params = query.value(idParams).toString();
            QStringList List_Params = string_Params.split(',');
            QVector<float> params;
            for (QStringList::iterator it = List_Params.begin(); it != List_Params.end(); ++it) {
                if(*it != ",") {
                    params.push_back(it->toFloat());
                }
            }
            new_effect.setParams(params);

            QString string_areaSize = query.value(idSize).toString();
            QStringList List_areaSize = string_Params.split(',');
            QVector<int> areaSize;
            for (QStringList::iterator it = List_areaSize.begin(); it != List_areaSize.end(); ++it) {
                if(*it != ",") {
                    areaSize.push_back(int(it->toFloat()));
                }
            }
            new_effect.setAreaSize(areaSize);
            new_effect.setAction(get_action(query.value(idAction).toInt()));
        }
    } else {
        qWarning() << "echec";
    }
    return new_effect;
}

bool c_dbmanager::add_action(c_action new_action) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.action (id,description,effect)"
                  "VALUES (:id, :description, :effect)");
    query.bindValue(":id", new_action.getId());
    query.bindValue(":description", new_action.getDescription());
    query.bindValue(":effect", new_action.getEffect());

    return query.exec();
}

c_action c_dbmanager::get_action(const int id) {
    QSqlQuery query(m_db);
    c_action action;
    query.prepare("SELECT *  FROM wakfu_builder.action "
                  "WHERE id = :id");
    query.bindValue(":id",id);
    if (query.exec()) {
        int id = query.record().indexOf("id");
        int idDescription = query.record().indexOf("description");
        int idEffect = query.record().indexOf("effect");
        while (query.next()) {
            action.setId(query.value(id).toInt());
            action.setDescription(query.value(idDescription).toString());
            action.setEffect(query.value(idEffect).toString());
        }
    } else {
        qWarning() << "echec";
    }
    return action;
}

bool c_dbmanager::add_itemProperty(c_itemProperties new_property) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.itemproperties (id,name,description)"
                  "VALUES (:id, :name, :description)");
    query.bindValue(":id", new_property.getId());
    query.bindValue(":name", new_property.getName());
    query.bindValue(":description", new_property.getDescription());

    return query.exec();
}

c_itemProperties c_dbmanager::get_itemProperty(const int id) {
    QSqlQuery query(m_db);
    c_itemProperties itemProperties;
    query.prepare("SELECT *  FROM wakfu_builder.itemproperties "
                  "WHERE id = :id");
    query.bindValue(":id",id);
    if (query.exec()) {
        int id = query.record().indexOf("id");
        int idDescription = query.record().indexOf("description");
        int idName = query.record().indexOf("name");
        while (query.next()) {
            itemProperties.setId(query.value(id).toInt());
            itemProperties.setDescription(query.value(idDescription).toString());
            itemProperties.setName(query.value(idName).toString());
        }
    } else {
        qWarning() << "echec";
    }
    return  itemProperties;
}

bool c_dbmanager::add_equipmentItemType(c_equipmentItemTypes new_type) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.equipmentItemType (id,parentId,recyclable,visibleInAnimation,title)"
                  "VALUES (:id, :parentId, :recyclable, :visibleInAnimation, :title)");
    query.bindValue(":id", new_type.getId());
    query.bindValue(":parentId", new_type.getParentId());
    query.bindValue(":recyclable", new_type.isRecyclable());
    query.bindValue(":visibleInAnimation", new_type.isVisibleInAnimation());
    query.bindValue(":title", new_type.getTitle());
    if(!query.exec()) {
        return false;
    }
    query.clear();

    int positionId;
    QStringList eqpPosition = new_type.getEquipementPositions();
    QStringList eqpDisablePosition = new_type.getEquipementDisablePositions();
    for (QStringList::iterator it = eqpPosition.begin(); it != eqpPosition.end(); ++it) {
        if (!PositionTypeList.contains(*it)) {
            if (add_equipmentPosition(*it,int(PositionTypeList.size()+1))) {
                PositionTypeList.append(*it);
                positionId = PositionTypeList.size();
            } else {
                return false;
            }
        } else {
          positionId = PositionTypeList.indexOf(*it) + 1;
        }
        add_relation_equipementType_Position(new_type.getId(),positionId);
    }

    for (QStringList::iterator it = eqpDisablePosition.begin(); it != eqpDisablePosition.end(); ++it) {
        if (!PositionTypeList.contains(*it)) {
            if (add_equipmentPosition(*it,int(PositionTypeList.size()+1))) {
                PositionTypeList.append(*it);
                positionId = PositionTypeList.size();
            } else {
                qWarning() << "Erreur dans l'ajout d'une nouvelle position";
                return false;
            }
        } else {
          positionId = PositionTypeList.indexOf(*it) + 1 ;
        }
        add_relation_equipementType_PositionDisable(new_type.getId(),positionId);
    }
    return true;
}

c_equipmentItemTypes c_dbmanager::get_equipmentItemType(const int id) {
    c_equipmentItemTypes eqpType;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM wakfu_builder.equipmentItemType "
                  "WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec()) {
        int idParent = query.record().indexOf("parentId");
        int idRecycl = query.record().indexOf("recyclable");
        int idVisible = query.record().indexOf("visibleInAnimation");
        int idTitle = query.record().indexOf("title");
        while (query.next()) {
            eqpType.setId(id);
            eqpType.setParentId(query.value(idParent).toInt());
            eqpType.setRecyclable(query.value(idRecycl).toBool());
            eqpType.setVisibleInAnimation(query.value(idVisible).toInt());
            eqpType.setTitle(query.value(idTitle).toString());
        }
        query.clear();
        query.prepare("SELECT * FROM "
                        "wakfu_builder.equipmentPosition as equi, "
                        "wakfu_builder.eqpType_Pos_relation as rel "
                      "WHERE equi.id = rel.id_Pos "
                        "AND rel.id_ET = :id");
        query.bindValue(":id",id);
        QStringList equipementPosition;
        if(query.exec()) {
            int id_name = query.record().indexOf("equipmentposition.name");
            while (query.next()) {
                equipementPosition << query.record().value(id_name).toString();
            }
        }
        eqpType.setEquipementPositions(equipementPosition);
        query.clear();
        query.prepare("SELECT * FROM "
                        "wakfu_builder.equipmentPosition as equi, "
                        "wakfu_builder.eqpType_DisPos_relation as rel "
                      "WHERE equi.id = rel.id_Pos "
                        "AND rel.id_ET = :id");
        query.bindValue(":id",id);
        QStringList equipementPositionDisable;
        if(query.exec()) {
            int id_name = query.record().indexOf("equipmentPosition.name");
            while (query.next()) {
                equipementPositionDisable << query.record().value(id_name).toString();
            }
        }
        eqpType.setEquipementDisablePositions(equipementPositionDisable);
    }
    return eqpType;
}

bool c_dbmanager::add_equipmentPosition(QString name, int id) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.equipmentPosition (id,name) "
                  "VALUES (:id, :name)");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    return query.exec();
}

QString c_dbmanager::get_equipmentPosition(int id) {
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM wakfu_builder.equipmentPosition "
                  "WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        int idName = query.record().indexOf("name");
        while (query.next()) {
            return query.value(idName).toString();
        }
    }
    return QString();
}
int get_equipmentPositionId(QString name);

QStringList c_dbmanager::get_AllEquipementPosition() {
    QStringList list;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM wakfu_builder.equipmentPosition "
                  "ORDER BY id ASC");
    if (query.exec()) {
        int idName = query.record().indexOf("name");
        while (query.next()) {
              list.append(query.value(idName).toString());
        }
    }
    return list;
}

bool c_dbmanager::add_relation_equipementType_Position(int equipementTypeId, int positionId) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.eqpType_Pos_relation (id_ET,id_Pos)"
                  "VALUES (:id_ET, :id_Pos)");
    query.bindValue(":id_ET", equipementTypeId);
    query.bindValue(":id_Pos", positionId);

    return query.exec();
}

bool c_dbmanager::add_relation_equipementType_PositionDisable(int equipementTypeId, int positionId) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.eqpType_DisPos_relation (id_ET,id_Pos)"
                  "VALUES (:id_ET, :id_Pos)");
    query.bindValue(":id_ET", equipementTypeId);
    query.bindValue(":id_Pos", positionId);

    return query.exec();
}

bool c_dbmanager::add_item(c_item item) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.item (id,  lvl,  itemTypeId,  itemSetId,  rarity,  bindType,  minimumShardSlotNumber,  maximumShardSlotNumber,  useApCost,  useMpCost,  useWpCost,  useMinRange,  useMaxRange,  useTestFreeCell,  useTestLos,  useTestOnlyLine,  useTestNoBorderCell,  useWorldTarget,  gfxId,  title, description,isFinal) "
                  "VALUES          (:id, :lvl, :itemTypeId, :itemSetId, :rarity, :bindType, :minimumShardSlotNumber, :maximumShardSlotNumber, :useApCost, :useMpCost, :useWpCost, :useMinRange, :useMaxRange, :useTestFreeCell, :useTestLos, :useTestOnlyLine, :useTestNoBorderCell, :useWorldTarget, :gfxId, :title, :description, :isFinal)");
    query.bindValue(":id", item.getId());
    query.bindValue(":itemTypeId", item.getType().getId());
    query.bindValue(":itemSetId", item.getSetId());
    query.bindValue(":rarity", item.getRarity());
    query.bindValue(":bindType", item.getBindType());
    query.bindValue(":minimumShardSlotNumber", item.getMinShardNumber());
    query.bindValue(":maximumShardSlotNumber", item.getMaxShardNumber());
    query.bindValue(":useApCost", item.getApUseCost());
    query.bindValue(":useMpCost", item.getMpUseCost());
    query.bindValue(":useWpCost", item.getWpUseCost());
    query.bindValue(":useMinRange", item.getMinRange());
    query.bindValue(":useMaxRange", item.getMaxRange());
    query.bindValue(":useTestFreeCell", item.TestFreeCell());
    query.bindValue(":useTestLos", item.TestLos());
    query.bindValue(":useTestOnlyLine", item.TestOnlyLine());
    query.bindValue(":useTestNoBorderCell", item.TestNoBorderCell());
    query.bindValue(":useWorldTarget", item.useWorldTarget());
    query.bindValue(":gfxId", item.getGfxId());
    query.bindValue(":title", item.getName());
    query.bindValue(":description",item.getDescription());
    query.bindValue(":isFinal",item.getIsFinal());

    if (item.getType().getId() == 582 || item.getType().getId() == 611) {
        query.bindValue(":lvl", -1);
    } else {
        query.bindValue(":lvl", item.getLvl());
    }

    if(!query.exec()) {
        return false;
    }


    QVector<c_itemProperties> properties = item.getProperties();
    for (QVector<c_itemProperties>::iterator it = properties.begin(); it != properties.end(); ++it) {
        add_relation_item_property(item.getId(), it->getId());
    }

    QVector<c_effect> useEffect = item.getUseEffects();
    for (QVector<c_effect>::iterator it = useEffect.begin(); it != useEffect.end(); ++it) {
        add_effect(*it);
        add_relation_item_useEffect(item.getId(), it->getId());
    }

    QVector<c_effect> useCriticalEffects = item.getUseCriticalEffects();
    for (QVector<c_effect>::iterator it = useCriticalEffects.begin(); it != useCriticalEffects.end(); ++it) {
        add_effect(*it);
        add_relation_item_useCriEffect(item.getId(), it->getId());
    }

    QVector<c_effect> equipEffects = item.getEquipEffects();
    for (QVector<c_effect>::iterator it = equipEffects.begin(); it != equipEffects.end(); ++it) {
        add_effect(*it);
        add_relation_item_equipeEffect(item.getId(), it->getId());
    }

    QList<c_carac> carac_list = item.getList_bonuses();

    foreach (c_carac carac, carac_list) {
        add_carac(carac);
        add_relation_item_carac(item.getId(),carac.id);
    }

    return true;
}

c_item c_dbmanager::get_item(int id) {
    c_item asked_item;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM wakfu_builder.item "
                  "WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec()) {
        int idlvl = query.record().indexOf("lvl");
        int iditemTypeId = query.record().indexOf("itemTypeId");
        int iditemSetId = query.record().indexOf("itemSetId");
        int idrarity = query.record().indexOf("rarity");
        int idbindType = query.record().indexOf("bindType");
        int idMinShard = query.record().indexOf("minimumShardSlotNumber");
        int idMaxShard = query.record().indexOf("maximumShardSlotNumber");
        int idAp = query.record().indexOf("useApCost");
        int idMp = query.record().indexOf("useMpCost");
        int idWp = query.record().indexOf("useWpCost");
        int idMinR = query.record().indexOf("useMinRange");
        int idMaxR = query.record().indexOf("useMaxRange");
        int idFreeCell = query.record().indexOf("useTestFreeCell");
        int idLos = query.record().indexOf("useTestLos");
        int idOLine = query.record().indexOf("useTestOnlyLine");
        int idNBCell = query.record().indexOf("useTestNoBorderCell");
        int idWT = query.record().indexOf("useWorldTarget");
        int idgfxId = query.record().indexOf("gfxId");
        int idName = query.record().indexOf("title");
        int idDescription = query.record().indexOf("description");
        while (query.next()) {
             asked_item.setId(id);
             asked_item.setLvl(query.value(idlvl).toInt());
             asked_item.setType(get_equipmentItemType(query.value(iditemTypeId).toInt()));
             asked_item.setSetId(query.value(iditemSetId).toInt());
             asked_item.setRarity(query.value(idrarity).toInt());
             asked_item.setBindType(query.value(idbindType).toInt());
             asked_item.setMinShardeNumber(query.value(idMinShard).toInt());
             asked_item.setMaxShardNumber(query.value(idMaxShard).toInt());
             asked_item.setApUseCost(query.value(idAp).toInt());
             asked_item.setMpUseCost(query.value(idMp).toInt());
             asked_item.setWpUseCost(query.value(idWp).toInt());
             asked_item.setMinRange(query.value(idMinR).toInt());
             asked_item.setMaxRange(query.value(idMaxR).toInt());
             asked_item.setFreeCell(query.value(idFreeCell).toBool());
             asked_item.setLos(query.value(idLos).toBool());
             asked_item.setOnlyLine(query.value(idOLine).toBool());
             asked_item.setNoBorderCell(query.value(idNBCell).toBool());
             asked_item.setUseWorldTarget(query.value(idWT).toInt());
             asked_item.setGfxId(query.value(idgfxId).toInt());
             asked_item.setName(query.value(idName).toString());
             asked_item.setDescription(query.value(idDescription).toString());
        }
        QVector<c_itemProperties> properties;
        QSqlQuery s_query(m_db);
        s_query.prepare("SELECT ip.id,ip.name,ip.description FROM wakfu_builder.item AS it, wakfu_builder.item_properties_relation AS pr, wakfu_builder.itemproperties as ip "
                        "WHERE it.id = :id AND pr.id_item = it.id AND pr.id_property = ip.id");
        s_query.bindValue(":id", id);
        bool flag = s_query.exec();
        if (flag) {
            int idid = s_query.record().indexOf("id");
            int idName = s_query.record().indexOf("name");
            int iddescri = s_query.record().indexOf("description");
            while (s_query.next()) {
                int id = s_query.value(idid).toInt();
                QString name = s_query.value(idName).toString();
                QString desc = s_query.value(iddescri).toString();
                properties.push_back(c_itemProperties(id,name,desc));
            }
        }
        asked_item.setProperties(properties);

        QVector<c_effect> useEffect;
        s_query.clear();
        s_query.prepare("SELECT er.id_E FROM wakfu_builder.item AS it, wakfu_builder.item_useEffect_relation AS er "
                        "WHERE it.id = :id AND er.id_item = it.id");
        s_query.bindValue(":id", id);
        if (s_query.exec()) {
            int id = s_query.record().indexOf("id_E");
            while (s_query.next()) {
                useEffect.push_back(get_effect(s_query.value(id).toInt()));
            }
        }
        asked_item.setUseEffects(useEffect);

        QVector<c_effect> useCriticalEffect;
        s_query.clear();
        s_query.prepare("SELECT er.id_E FROM wakfu_builder.item AS it, wakfu_builder.item_useCriticalEffect_relation AS er "
                        "WHERE it.id = :id AND er.id_item = it.id");
        s_query.bindValue(":id", id);
        if (s_query.exec()) {
            int id = s_query.record().indexOf("id_E");
            while (s_query.next()) {
                useCriticalEffect.push_back(get_effect(s_query.value(id).toInt()));
            }
        }
        asked_item.setUseCriticalEffects(useCriticalEffect);

        QVector<c_effect> equipEffect;
        s_query.clear();
        s_query.prepare("SELECT er.id_E FROM wakfu_builder.item AS it, wakfu_builder.item_useEquipEffect_relation AS er "
                        "WHERE it.id = :id AND er.id_item = it.id");
        s_query.bindValue(":id", id);
        if (s_query.exec()) {
            int id = s_query.record().indexOf("id_E");
            while (s_query.next()) {
                equipEffect.push_back(get_effect(s_query.value(id).toInt()));
            }
        }
        asked_item.setEquipEffets(equipEffect);
    }
    return asked_item;
}

bool c_dbmanager::add_relation_item_property(int id_Item, int id_propertie) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.item_properties_relation (id_item,id_property)"
                  "VALUES (:id_ET, :id_property)");
    query.bindValue(":id_ET", id_Item);
    query.bindValue(":id_property", id_propertie);

    bool flag = query.exec();
    return flag;
}

bool c_dbmanager::add_relation_item_useEffect(int id_Item, int id_effect) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.item_useEffect_relation (id_item,id_E)"
                  "VALUES (:id_ET, :id_E)");
    query.bindValue(":id_ET", id_Item);
    query.bindValue(":id_E", id_effect);

    bool flag = query.exec();
    return flag;
}

bool c_dbmanager::add_relation_item_useCriEffect(int id_Item, int id_effect) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.item_useCriticalEffect_relation (id_item,id_E)"
                  "VALUES (:id_ET, :id_E)");
    query.bindValue(":id_ET", id_Item);
    query.bindValue(":id_E", id_effect);

    bool flag = query.exec();
    return flag;
}

bool c_dbmanager::add_relation_item_equipeEffect(int id_Item, int id_effect) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.item_useEquipEffect_relation (id_item,id_E)"
                  "VALUES (:id_ET, :id_E)");
    query.bindValue(":id_ET", id_Item);
    query.bindValue(":id_E", id_effect);

    bool flag = query.exec();
    return flag;
}

QList<int> c_dbmanager::getImagesList() {
    QSqlQuery query(m_db);
    QList<int> image_name;
    query.prepare("SELECT gfxid from wakfu_builder.item");
    if (query.exec()) {
        int gfxid = query.record().indexOf("gfxid");
        while (query.next()) {
            image_name.push_back(query.value(gfxid).toInt());
        }
    }
    return image_name;

}

QList<int> c_dbmanager::getItemListId() {
    QSqlQuery query(m_db);
    QList<int> id_item;
    query.prepare("SELECT id from wakfu_builder.item");
    if (query.exec()) {
        int id = query.record().indexOf("id");
        while (query.next()) {
            id_item.push_back(query.value(id).toInt());
        }
    }
    return id_item;
}

QList<c_item> c_dbmanager::getAllItem() {
    QList<c_item> item_list;
    QSqlQuery query(m_db);
    QElapsedTimer timer;
    QElapsedTimer timer_2;
    c_item asked_item;
    c_equipmentItemTypes equipmentType;
    timer.start();
    query.prepare("SELECT * FROM wakfu_builder.equipmentItemType as et, wakfu_builder.item as it WHERE it.itemTypeId = et.id");
    if (query.exec()) {
        int id_item = query.record().indexOf("item.id");
        int idlvl = query.record().indexOf("lvl");
        int iditemSetId = query.record().indexOf("itemSetId");
        int idrarity = query.record().indexOf("rarity");
        int idbindType = query.record().indexOf("bindType");
        int idMinShard = query.record().indexOf("minimumShardSlotNumber");
        int idMaxShard = query.record().indexOf("maximumShardSlotNumber");
        int idAp = query.record().indexOf("useApCost");
        int idMp = query.record().indexOf("useMpCost");
        int idWp = query.record().indexOf("useWpCost");
        int idMinR = query.record().indexOf("useMinRange");
        int idMaxR = query.record().indexOf("useMaxRange");
        int idName = query.record().indexOf("item.title");
        int idDescription = query.record().indexOf("description");

        int id_equip = query.record().indexOf("equipmentItemType.id");
        int id_equip_title = query.record().indexOf("equipmentItemType.title");

        timer.restart();
        qint64 time = 0;
        while (query.next()) {
            asked_item.setId(query.value(id_item).toInt());
            asked_item.setLvl(query.value(idlvl).toInt());
            asked_item.setSetId(query.value(iditemSetId).toInt());
            asked_item.setRarity(query.value(idrarity).toInt());
            asked_item.setBindType(query.value(idbindType).toInt());
            asked_item.setMinShardeNumber(query.value(idMinShard).toInt());
            asked_item.setMaxShardNumber(query.value(idMaxShard).toInt());
            asked_item.setApUseCost(query.value(idAp).toInt());
            asked_item.setMpUseCost(query.value(idMp).toInt());
            asked_item.setWpUseCost(query.value(idWp).toInt());
            asked_item.setMinRange(query.value(idMinR).toInt());
            asked_item.setMaxRange(query.value(idMaxR).toInt());
            asked_item.setName(query.value(idName).toString());
            asked_item.setDescription(query.value(idDescription).toString());
            timer_2.start();
            item_list.append(asked_item);
            time += timer_2.nsecsElapsed();
            timer_2.restart();

            equipmentType.setId(query.value(id_equip).toInt());
            equipmentType.setTitle(query.value(id_equip_title).toString());
            asked_item.setType(equipmentType);
        }
    }
    return item_list;
}

bool c_dbmanager::add_state(c_state state) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.states (id,name,description)"
                  "VALUES (:id, :name, :description)");
    query.bindValue(":id", state.get_id());
    query.bindValue(":name", state.get_name());
    query.bindValue(":description",state.get_description());

    bool flag = query.exec();
    return flag;
}

c_state c_dbmanager::get_state(int id) {
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM wakfu_builder.states "
                  "WHERE id = :id");
    query.bindValue(":id", id);
    c_state state;
    if (query.exec()) {
        int idName = query.record().indexOf("name");
        int idDescri = query.record().indexOf("description");
        while (query.next()) {
            state.set_id(id);
            state.set_name(query.value(idName).toString());
            state.set_description(query.value(idDescri).toString());
        }
    }
    return state;
}

QList<int> c_dbmanager::getid_item_from_actions(QList<QString> carac_effect, QList<int> rarities, QList<int> types, QList<int> bondaries, QString name, bool final, QList<bool> condi) {
    QList<int> res;
    QSqlQuery query(m_db);
    QString query_string;
    if (!condi.isEmpty()) {
        query_string = prepareQuery_condi(carac_effect,rarities,types,bondaries,name,final,condi);
    } else {
        query_string = prepareQuery_simple(carac_effect,rarities,types,bondaries,name,final);
    }
    query.prepare(query_string);
    for (int i = 0; i < rarities.size(); ++i) {
        query.bindValue(QString(":rarity%1").arg(i),rarities.at(i));
    }
    for (int i = 0; i < types.size(); ++i) {
        query.bindValue(QString(":types%1").arg(i),types.at(i));
    }
    for (int i = 0; i < carac_effect.size(); ++i) {
        query.bindValue(QString(":carac_effect%1").arg(i),carac_effect.at(i));
    }
    if (query.exec()) {
        int id = query.record().indexOf("id");
        while (query.next()) {
            res.push_back(query.value(id).toInt());
        }
    } else {
        qDebug() << query.lastError();
    }
    qDebug() << query_string;
    qDebug() << query.boundValues();
    return res;
}

QList<int> c_dbmanager::getid_item_from_actions_sorted(QList<QString> carac_effect, QList<int> rarities, QList<int> types, QList<int> bondaries, QString name, bool final, QList<bool> condi) {
    QList<int> res;
    QSqlQuery query(m_db);
    QString query_string = prepareQuery_condi(carac_effect,rarities,types,bondaries,name,final,condi);
    QString query_string_sorted = QString("SELECT item.id,sum(carac.value) FROM ( %1 ) as item INNER JOIN wakfu_builder.relation_item_carac as r_item_carac ON item.id = r_item_carac.id_item INNER JOIN wakfu_builder.carac as carac ON r_item_carac.id_carac = carac.id WHERE ").arg(query_string);
    if (carac_effect.size() != 0) {
        query_string_sorted += "( carac.effect = :carac_effect0 OR";
        for (int i = 1; i < carac_effect.size(); ++i) {
            query_string_sorted += QString(" carac.effect = :carac_effect%1 OR").arg(i);
        }
        query_string_sorted.remove(QRegExp("OR$"));
        query_string_sorted += ")";
    }
    query_string_sorted += "GROUP BY item.id ORDER BY sum(carac.value) DESC";

    query.prepare(query_string_sorted);
    for (int i = 0; i < rarities.size(); ++i) {
        query.bindValue(QString(":rarity%1").arg(i),rarities.at(i));
    }
    for (int i = 0; i < types.size(); ++i) {
        query.bindValue(QString(":types%1").arg(i),types.at(i));
    }
    for (int i = 0; i < carac_effect.size(); ++i) {
        query.bindValue(QString(":carac_effect%1").arg(i),carac_effect.at(i));
    }

    if (query.exec()) {
        int id = query.record().indexOf("id");
        while (query.next()) {
            res.push_back(query.value(id).toInt());
        }
    } else {
        qDebug() << query.lastError();
    }
    qDebug() << query_string;
    qDebug() << query.boundValues();
    return res;
}

QList<c_item> c_dbmanager::getItems(QList<int> ids) {
    QList<c_item> res;
    QSqlQuery query(m_db);
    QString query_string;
    query_string = "SELECT * FROM wakfu_builder.equipmentItemType as et, wakfu_builder.item as item WHERE item.itemTypeId = et.id AND (";
    for (int i = 0; i < ids.size(); ++i) {
       query_string.push_back(QString(" item.id = %1 OR").arg(ids.at(i)));
    }
    query_string.remove(QRegExp("OR$"));
    query_string.push_back(")");
    query_string.push_back("ORDER BY item.lvl DESC");
    if (query.exec(query_string)) {
        while (query.next()) {
            c_item item = getItemFromQueryLite(query);
            res.push_back(item);
        }
    }
    return res;
}

c_item c_dbmanager::getItemFromQueryLite(QSqlQuery query) {
    c_item asked_item;
    int id_item = query.record().indexOf("item.id");
    int idlvl = query.record().indexOf("lvl");
    int iditemSetId = query.record().indexOf("itemSetId");
    int idrarity = query.record().indexOf("rarity");
    int idbindType = query.record().indexOf("bindType");
    int idMinShard = query.record().indexOf("minimumShardSlotNumber");
    int idMaxShard = query.record().indexOf("maximumShardSlotNumber");
    int idAp = query.record().indexOf("useApCost");
    int idMp = query.record().indexOf("useMpCost");
    int idWp = query.record().indexOf("useWpCost");
    int idMinR = query.record().indexOf("useMinRange");
    int idMaxR = query.record().indexOf("useMaxRange");
    int idName = query.record().indexOf("item.title");
    int idDescription = query.record().indexOf("description");
    int idGfxId = query.record().indexOf("gfxid");

    int id_equip = query.record().indexOf("equipmentItemType.id");
    int id_equip_title = query.record().indexOf("equipmentItemType.title");

    asked_item.setId(query.value(id_item).toInt());
    asked_item.setLvl(query.value(idlvl).toInt());
    asked_item.setSetId(query.value(iditemSetId).toInt());
    asked_item.setRarity(query.value(idrarity).toInt());
    asked_item.setBindType(query.value(idbindType).toInt());
    asked_item.setMinShardeNumber(query.value(idMinShard).toInt());
    asked_item.setMaxShardNumber(query.value(idMaxShard).toInt());
    asked_item.setApUseCost(query.value(idAp).toInt());
    asked_item.setMpUseCost(query.value(idMp).toInt());
    asked_item.setWpUseCost(query.value(idWp).toInt());
    asked_item.setMinRange(query.value(idMinR).toInt());
    asked_item.setMaxRange(query.value(idMaxR).toInt());
    asked_item.setName(query.value(idName).toString());
    asked_item.setDescription(query.value(idDescription).toString());
    asked_item.setGfxId(query.value(idGfxId).toInt());
    c_equipmentItemTypes equipmentType;
    equipmentType.setId(query.value(id_equip).toInt());
    equipmentType.setTitle(query.value(id_equip_title).toString());
    asked_item.setType(equipmentType);
    return asked_item;
}

QVector<c_effect> c_dbmanager::getUseEffectFromItemId(int id) {
    QVector<c_effect> useEffect;
    QSqlQuery s_query(m_db);
    s_query.clear();
    s_query.prepare("SELECT er.id_E FROM wakfu_builder.item AS it, wakfu_builder.item_useEffect_relation AS er "
                    "WHERE it.id = :id AND er.id_item = it.id");
    s_query.bindValue(":id", id);
    if (s_query.exec()) {
        int id = s_query.record().indexOf("id_E");
        while (s_query.next()) {
            useEffect.push_back(get_effect(s_query.value(id).toInt()));
        }
    }
    return useEffect;
}

QVector<c_effect> c_dbmanager::getEquipEffectFromItemId(int id) {
    QVector<c_effect> equipEffect;
    QSqlQuery s_query(m_db);
    s_query.clear();
    s_query.prepare("SELECT er.id_E FROM wakfu_builder.item AS it, wakfu_builder.item_useEquipEffect_relation AS er "
                    "WHERE it.id = :id AND er.id_item = it.id");
    s_query.bindValue(":id", id);
    if (s_query.exec()) {
        int id = s_query.record().indexOf("id_E");
        while (s_query.next()) {
            equipEffect.push_back(get_effect(s_query.value(id).toInt()));
        }
    }
    return equipEffect;
}

int c_dbmanager::add_save_builder(QString json, QString name, int lvl) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.builder_save (json,name,niveau) VALUES (:json,:name,:lvl)");
    query.bindValue(":json",json);
    query.bindValue(":lvl",lvl);
    query.bindValue(":name",name);
    if (query.exec()) {
        QSqlQuery s_query(m_db);
        s_query.prepare("SELECT LASTVAL()");
        if (s_query.exec()) {
            int id = s_query.record().indexOf("lastval");
            while (s_query.next()) {
                return s_query.value(id).toInt();
            }
        }
    }
    return 0;
}

int c_dbmanager::update_save_builder(QString json, int id, QString name, int lvl) {
    QSqlQuery query(m_db);
    query.prepare("UPDATE wakfu_builder.builder_save SET json = :json, name = :name, niveau = :lvl  WHERE id = :id");
    query.bindValue(":json",json);
    query.bindValue(":id",id);
    query.bindValue(":lvl",lvl);
    query.bindValue(":name",name);
    if (query.exec()) {
        return 1;
    }
    return 0;
}

QSqlDatabase c_dbmanager::getDb() const
{
    return m_db;
}

bool c_dbmanager::add_carac(c_carac carac) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.carac (id,effect,value) "
                  "VALUES (:id, :effect, :value)");
    query.bindValue(":id", carac.id);
    query.bindValue(":effect", carac.effect);
    query.bindValue(":value", carac.value);

    bool flag = query.exec();
    return flag;
}

c_carac c_dbmanager::get_carac(int id) {
    QSqlQuery query(m_db);
    query.prepare("SELECT *  FROM wakfu_builder.carac "
                  "WHERE id = :id");
    query.bindValue(":id",id);
    c_carac carac;
    if (query.exec()) {
        int id = query.record().indexOf("id");
        int idEffect = query.record().indexOf("effect");
        int idValue = query.record().indexOf("effect");
        while (query.next()) {
            carac.id = query.value(id).toInt();
            carac.effect = query.value(idEffect).toString();
            carac.value = query.value(idValue).toInt();
        }
    } else {
        qWarning() << "echec";
    }
    return carac;
}

bool c_dbmanager::add_relation_item_carac(int id_item, int id_carac) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO wakfu_builder.relation_item_carac (id_item,id_carac) "
                  "VALUES (:id_item, :id_carac)");
    query.bindValue(":id_item", id_item);
    query.bindValue(":id_carac", id_carac);
    bool flag = query.exec();
    return flag;
}

QString c_dbmanager::prepareQuery_simple(QList<QString> carac_effect, QList<int> rarities, QList<int> types, QList<int> bondaries, QString name, bool final) {
    QString query_string;
    query_string = "SELECT item.id,item.lvl FROM wakfu_builder.item as item ";
    for (int i = 0; i< carac_effect.size(); ++i) {
        query_string += QString(", wakfu_builder.carac as carac%1, wakfu_builder.relation_item_carac as relation%1").arg(i);
    }
    query_string += QString(" WHERE (item.lvl >= %1 AND item.lvl <= %2 %3) %4 AND").arg(bondaries.at(0)).arg(bondaries.at(1)).arg(types.contains(c_item::mapTypeToId["PET"])||types.contains(c_item::mapTypeToId["MOUNT"])?"OR item.lvl = -1":"").arg(final?"AND isFinal = true":"");

    if (!carac_effect.isEmpty()) {
        for (int i = 0; i < carac_effect.size(); ++i) {
            query_string += QString(" item.id = relation%1.id_item AND").arg(i);
        }
        for (int i = 0; i < carac_effect.size(); ++i) {
            query_string += QString(" relation%1.id_carac = carac%1.id AND").arg(i);
        }

        for (int i = 0; i < carac_effect.size(); ++i) {
            query_string += QString(" carac%1.effect = :carac_effect%1 AND").arg(i);
        }
        query_string.remove(QRegExp("AND$"));
        query_string.remove(QRegExp("OR$"));
        query_string.append(" AND");
    }
    if (!rarities.isEmpty()) {
        query_string += (" ( ");
        for (int i = 0; i < rarities.size(); ++i) {
            query_string += QString(" item.rarity = :rarity%1 OR").arg(i);
        }
        query_string.remove(QRegExp("OR$"));
        query_string += (" ) ");
        query_string.append(" AND");
    }
    if (!types.isEmpty()) {
        query_string += (" ( ");
        for (int i = 0; i < types.size(); ++i) {
            query_string += QString(" item.itemTypeId = :types%1 OR").arg(i);
        }
        query_string.remove(QRegExp("OR$"));
        query_string += (" ) ");
        query_string.append(" AND");
    }
    if (!name.isEmpty()) {
        query_string.append(QString(" item.title LIKE '\%%1\%' ").arg(name));
        query_string.append(" AND");
    }
    query_string.remove(QRegExp("AND$"));
    query_string.remove(QRegExp("WHERE$"));
    query_string.push_back(" GROUP BY item.id,item.lvl ORDER BY item.lvl ASC");
    return query_string;
}

QString c_dbmanager::prepareQuery_condi(QList<QString> carac_effect, QList<int> rarities, QList<int> types, QList<int> bondaries, QString name, bool final, QList<bool> condi) {
    QString query_string;
    query_string = "SELECT item.id,item.lvl FROM wakfu_builder.item as item ";
    for (int i = 0; i< carac_effect.size(); ++i) {
        query_string += QString(", wakfu_builder.carac as carac%1, wakfu_builder.relation_item_carac as relation%1").arg(i);
    }
    query_string += QString(" WHERE (item.lvl >= %1 AND item.lvl <= %2 %3) %4 AND").arg(bondaries.at(0)).arg(bondaries.at(1)).arg(types.contains(c_item::mapTypeToId["PET"])||types.contains(c_item::mapTypeToId["MOUNT"])?"OR item.lvl = -1":"").arg(final?"AND isFinal = true":"");

    if (!carac_effect.isEmpty()) {
        for (int i = 0; i < carac_effect.size(); ++i) {
            query_string += QString(" item.id = relation%1.id_item AND").arg(i);
        }
        for (int i = 0; i < carac_effect.size(); ++i) {
            query_string += QString(" relation%1.id_carac = carac%1.id AND").arg(i);
        }
        query_string += generateCombiQuery_carac(condi);
        query_string.remove(QRegExp("AND$"));
        query_string.remove(QRegExp("OR$"));
        query_string.append(" AND");
    }
    if (!rarities.isEmpty()) {
        query_string += (" ( ");
        for (int i = 0; i < rarities.size(); ++i) {
            query_string += QString(" item.rarity = :rarity%1 OR").arg(i);
        }
        query_string.remove(QRegExp("OR$"));
        query_string += (" ) ");
        query_string.append(" AND");
    }
    if (!types.isEmpty()) {
        query_string += (" ( ");
        for (int i = 0; i < types.size(); ++i) {
            query_string += QString(" item.itemTypeId = :types%1 OR").arg(i);
        }
        query_string.remove(QRegExp("OR$"));
        query_string += (" ) ");
        query_string.append(" AND");
    }
    if (!name.isEmpty()) {
        query_string.append(QString(" item.title LIKE '\%%1\%' ").arg(name));
        query_string.append(" AND");
    }
    query_string.remove(QRegExp("AND$"));
    query_string.remove(QRegExp("WHERE$"));
    query_string.push_back(" GROUP BY item.id,item.lvl ORDER BY item.lvl DESC");
    return query_string;
}

bool c_dbmanager::setFinal(QList<int> isFinalList) {
    QSqlQuery query(m_db);
    QString query_string("UPDATE wakfu_builder.item isFinal = false WHERE ");
    foreach (int id, isFinalList) {
        query_string.append(QString(" id = %1 OR").arg(id));
    }
    query_string.remove(QRegExp("OR$"));
    query.prepare(query_string);
    bool flag = query.exec();
    return flag;
}

void c_dbmanager::empty_database() {
    QSqlQuery query(m_db);
    QString query_string("delete from wakfu_builder.action;"
                         "delete from wakfu_builder.itemproperties;"
                         "delete from wakfu_builder.equipmentItemType;"
                         "delete from wakfu_builder.equipmentPosition;"
                         "delete from wakfu_builder.eqpType_Pos_relation;"
                         "delete from wakfu_builder.eqpType_DisPos_relation;"

                         "delete from wakfu_builder.effect;"
                         "delete from wakfu_builder.item;"
                         "delete from wakfu_builder.item_properties_relation;"
                         "delete from wakfu_builder.item_useEffect_relation;"
                         "delete from wakfu_builder.item_useCriticalEffect_relation;"
                         "delete from wakfu_builder.item_useEquipEffect_relation;"
                         "delete from wakfu_builder.carac");
}

void c_dbmanager::check_structure() {
    QSqlQuery query(m_db);
    qDebug() << m_db.tables();
    if (!m_db.tables().contains("wakfu_builder.relation_item_carac") || (get_number_column("relation_item_carac") != 2)) {
        debug_check_table_structure("relation_item_carac",3);
        query.exec("DROP TABLE wakfu_builder.relation_item_carac");
        query.exec("CREATE TABLE wakfu_builder.relation_item_carac( id_item integer, id_carac integer, PRIMARY KEY(id_item,id_carac));");
        qDebug() << "relation_item_carac table created";
    }
    if (!m_db.tables().contains("wakfu_builder.eqptype_pos_relation") || (get_number_column("eqptype_pos_relation") != 2)) {
        debug_check_table_structure("eqptype_pos_relation",2);
        query.exec("DROP TABLE wakfu_builder.eqptype_pos_relation");
        query.exec("CREATE TABLE wakfu_builder.eqptype_pos_relation(id_ET integer, id_Pos integer, CONSTRAINT relation_pos_pk PRIMARY KEY(id_ET,id_Pos))");
        qDebug() << "eqptype_pos_relation table created";
    }
    if (!m_db.tables().contains("wakfu_builder.eqptype_dispos_relation") || (get_number_column("eqptype_dispos_relation") != 2)) {
        debug_check_table_structure("eqptype_dispos_relation",2);
        query.exec("DROP TABLE wakfu_builder.eqptype_dispos_relation");
        query.exec("CREATE TABLE wakfu_builder.eqptype_dispos_relation (id_ET integer, id_Pos integer, CONSTRAINT relation_disPos_pk PRIMARY KEY(id_ET,id_Pos))");
        qDebug() << "eqptype_dispos_relation table created";
    }
    if (!m_db.tables().contains("wakfu_builder.item_properties_relation") || (get_number_column("item_properties_relation") != 2)) {
        debug_check_table_structure("item_properties_relation",2);
        query.exec("DROP TABLE wakfu_builder.item_properties_relation");
        query.exec("CREATE TABLE wakfu_builder.item_properties_relation(id_item integer, id_property integer, CONSTRAINT relation_prop_pk PRIMARY KEY(id_item,id_property));");
        qDebug() << "item_properties_relation table created";
    }
    if (!m_db.tables().contains("wakfu_builder.item_useeffect_relation") || (get_number_column("item_useeffect_relation") != 2)) {
        debug_check_table_structure("item_useeffect_relation",2);
        query.exec("DROP TABLE wakfu_builder.item_useeffect_relation");
        query.exec("CREATE TABLE wakfu_builder.item_useeffect_relation (id_item integer, id_E integer, PRIMARY KEY(id_item,id_E))");
        qDebug() << "item_useeffect_relation table created";
    }
    if (!m_db.tables().contains("wakfu_builder.item_usecriticaleffect_relation") || (get_number_column("item_usecriticaleffect_relation") != 2)) {
        debug_check_table_structure("item_usecriticaleffect_relation",2);
        query.exec("DROP TABLE wakfu_builder.item_usecriticaleffect_relation");
        query.exec("CREATE TABLE wakfu_builder.item_usecriticaleffect_relation (id_item integer, id_E integer, CONSTRAINT relation_uCE_pk PRIMARY KEY(id_item,id_E))");
        qDebug() << "item_usecriticaleffect_relation table created";
    }
    if (!m_db.tables().contains("wakfu_builder.item_useequipeffect_relation") || (get_number_column("item_useequipeffect_relation") != 2)) {
        debug_check_table_structure("item_useequipeffect_relation",2);
        query.exec("DROP TABLE wakfu_builder.item_useequipeffect_relation");
        query.exec("CREATE TABLE wakfu_builder.item_useequipeffect_relation (id_item integer, id_E integer, CONSTRAINT relation_uEE_pk PRIMARY KEY(id_item,id_E))");
        qDebug() << "item_useequipeffect_relation table created";
    }
    if (!m_db.tables().contains("wakfu_builder.action") || (get_number_column("action") != 3)) {
        debug_check_table_structure("action",2);
        query.exec("DROP TABLE wakfu_builder.action");
        query.exec("CREATE TABLE wakfu_builder.action (id integer PRIMARY KEY, description text, effect text)");
        qDebug() << "action table created";
    }
    if (!m_db.tables().contains("wakfu_builder.effect") || (get_number_column("effect") != 6)) {
        debug_check_table_structure("effect",6);
        query.exec("DROP TABLE wakfu_builder.effect");
        query.exec("CREATE TABLE wakfu_builder.effect (id integer PRIMARY KEY, actionId integer,areaShape integer, areaSize text, params text, description text)");
        qDebug() << "effect table created";
    }
    if (!m_db.tables().contains("wakfu_builder.itemproperties") || (get_number_column("itemproperties") != 3)) {
        debug_check_table_structure("itemproperties",3);
        query.exec("DROP TABLE wakfu_builder.itemproperties");
        query.exec("CREATE TABLE wakfu_builder.itemproperties (id integer PRIMARY KEY, name text, description text)");
        qDebug() << "itemproperties table created";
    }
    if (!m_db.tables().contains("wakfu_builder.equipmentitemtype") || (get_number_column("equipmentitemtype") != 5)) {
        debug_check_table_structure("equipmentitemtype",5);
        query.exec("DROP TABLE wakfu_builder.equipmentitemtype");
        query.exec("CREATE TABLE wakfu_builder.equipmentitemtype (id integer PRIMARY KEY, parentId integer, recyclable bool, visibleInAnimation bool, title text);");
        qDebug() << "equipmentitemtype table created";
    }
    if (!m_db.tables().contains("wakfu_builder.equipmentposition") || (get_number_column("equipmentposition") != 2)) {
        debug_check_table_structure("equipmentPosition",2);
        query.exec("DROP TABLE wakfu_builder.equipmentposition");
        query.exec("CREATE TABLE wakfu_builder.equipmentPosition (id integer PRIMARY KEY, name text)");
        qDebug() << "equipmentPosition table created";
    }
    if (!m_db.tables().contains("wakfu_builder.item") || (get_number_column("item") != 22)) {
        debug_check_table_structure("item",22);
        query.exec("DROP TABLE wakfu_builder.item");
        query.exec("CREATE TABLE wakfu_builder.item( id integer PRIMARY KEY, lvl integer, itemTypeId integer, itemSetId integer, rarity integer, bindType integer, minimumShardSlotNumber integer, maximumShardSlotNumber integer, useApCost integer, useMpCost integer, useWpCost integer, useMinRange integer, useMaxRange integer, useTestFreeCell bool, useTestLos bool, useTestOnlyLine bool, useTestNoBorderCell bool, useWorldTarget integer, gfxid integer, title text, description text, isFinal bool)");
        qDebug() << "item table created";
    }
    if (!m_db.tables().contains("wakfu_builder.carac") || (get_number_column("carac") != 3)) {
        debug_check_table_structure("carac",3);
        query.exec("DROP TABLE wakfu_builder.carac");
        query.exec("CREATE TABLE wakfu_builder.carac (id integer PRIMARY KEY, effect text, value integer)");
        qDebug() << "carac table created";
    }
    if (!m_db.tables().contains("wakfu_builder.builder_save") || (get_number_column("builder_save") != 4)) {
        debug_check_table_structure("builder_save",4);
        query.exec("DROP TABLE wakfu_builder.builder_save");
        query.exec(" CREATE TABLE wakfu_builder.builder_save (id SERIAL UNIQUE, json text, name text, niveau integer)");
        qDebug() << "builder_save table created";
    }
    if (!m_db.tables().contains("wakfu_builder.states") || (get_number_column("states") != 3)) {
        debug_check_table_structure("states",3);
        query.exec("DROP TABLE wakfu_builder.states");
        query.exec(" CREATE TABLE wakfu_builder.states (id integer PRIMARY KEY, name text, description text)");
        qDebug() << "states table created";
    }
}

void c_dbmanager::debug_check_table_structure(QString name, int size) {
    qDebug() << name << " :";
    qDebug() << "Exists :" << m_db.tables().contains(QString("wakfu_builder.%1").arg(name)) << " Supposed size : " << size << "Size : " << get_number_column(name);
}

int c_dbmanager::get_number_column(QString table) {
    QSqlQuery query(m_db);
    int number = 0;
    QString query_string(QString(" SELECT count(column_name) FROM information_schema.columns "
                         " WHERE table_schema = 'wakfu_builder' and table_name = '%1'").arg(table));
    //qDebug() << query_string;
    query.prepare(query_string);
    if(query.exec()) {
        //qDebug() << query.record();
        int id = query.record().indexOf("count");
        while (query.next()) {
            number = query.value(id).toInt();
        }
    }
    return number;
}

QString c_dbmanager::generateCombiQuery_carac(QList<bool> condi) {
    QString action;
    if (condi.isEmpty()) {
        action = QString(" carac0.effect = :carac_effect0 ");
    } else {
        action = QString(" %2 carac0.effect = :carac_effect0 %1 ").arg(condi.at(0)?"OR":"AND").arg(condi.at(0)?"(":"");
        for (int i = 1; i < condi.size(); ++i) {
            action += QString("%2 carac%1.effect = :carac_effect%1 %3 %4 ").arg(i).arg((!condi[i-1]&&condi[i])?"(":"").arg((condi[i-1]&&!condi[i])?")":"").arg(condi[i]?"OR":"AND");
        }
        if (condi.size()) {
            action += QString("carac%1.effect = :carac_effect%1 %2").arg(condi.size()).arg(condi.last()?")":"");
        }
    }
    return action;
}

