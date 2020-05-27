#include "c_dbmanager.h"

c_dbmanager::c_dbmanager() {
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("localhost");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setDatabaseName("postgres");
    m_db.setUserName("wakfu_builder");
    m_db.setPassword("hY5L*2u6<q");
    qDebug() << "Openning database :" << m_db.open();
}

c_dbmanager::~c_dbmanager() {
    QString database_name = m_db.connectionName();
    m_db.close();
    QSqlDatabase::removeDatabase(database_name);
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
                    params.push_back(int(it->toFloat()));
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
    query.prepare("INSERT INTO wakfu_builder.item (id,  lvl,  itemTypeId,  itemSetId,  rarity,  bindType,  minimumShardSlotNumber,  maximumShardSlotNumber,  useApCost,  useMpCost,  useWpCost,  useMinRange,  useMaxRange,  useTestFreeCell,  useTestLos,  useTestOnlyLine,  useTestNoBorderCell,  useWorldTarget,  gfxId,  title, description) "
                  "VALUES          (:id, :lvl, :itemTypeId, :itemSetId, :rarity, :bindType, :minimumShardSlotNumber, :maximumShardSlotNumber, :useApCost, :useMpCost, :useWpCost, :useMinRange, :useMaxRange, :useTestFreeCell, :useTestLos, :useTestOnlyLine, :useTestNoBorderCell, :useWorldTarget, :gfxId, :title, :description)");
    query.bindValue(":id", item.getId());
    query.bindValue(":lvl", item.getLvl());
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

    bool flag = query.exec();
    return flag;
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

QList<QPair<int,int>> c_dbmanager::getid_item_from_actions(QList<int> action_ids, QList<int> rarities, QList<int> types, QList<int> bondaries, QString name) {
    QList<QPair<int,int>> res;
    QSqlQuery query(m_db);
    QString query_string;
    query_string = "SELECT item.id,item.lvl FROM wakfu_builder.item as item";
    for (int i = 0; i< action_ids.size(); ++i) {
        query_string += QString(", wakfu_builder.effect as effect%1, wakfu_builder.item_useEquipEffect_relation as relation%1").arg(i);
    }
    query_string += QString(" WHERE item.lvl >= %1 AND item.lvl <= %2 ").arg(bondaries.at(0)).arg(bondaries.at(1));
    if (!action_ids.isEmpty()) {
        query_string.append("AND");
        for (int i = 0; i < action_ids.size(); ++i) {
            query_string += QString(" item.id = relation%1.id_item AND").arg(i);
        }
        //query_string.remove(QRegExp("AND$"));
        for (int i = 0; i < action_ids.size(); ++i) {
            query_string += QString(" relation%1.id_E = effect%1.id AND").arg(i);
        }
        for (int i = 0; i < action_ids.size(); ++i) {
            query_string += QString(" effect%1.actionId = :action_id%1 AND").arg(i);
        }
        query_string.remove(QRegExp("AND$"));
    }
    if (!rarities.isEmpty()) {
        query_string.append("AND");
        query_string += (" ( ");
        for (int i = 0; i < rarities.size(); ++i) {
            query_string += QString(" item.rarity = :rarity%1 OR").arg(i);
        }
        query_string.remove(QRegExp("OR$"));
        query_string += (" ) ");
    }
    if (!types.isEmpty()) {
        query_string.append("AND");
        query_string += (" ( ");
        for (int i = 0; i < types.size(); ++i) {
            query_string += QString(" item.itemTypeId = :types%1 OR").arg(i);
        }
        query_string.remove(QRegExp("OR$"));
        query_string += (" ) ");
    }
    query_string.remove(QRegExp("AND$"));
    if (!name.isEmpty()) {
        query_string.append(QString(" AND item.title LIKE '\%%1\%' ").arg(name));
    }
    query_string.push_back(" ORDER BY item.lvl DESC");
    query.prepare(query_string);
    for (int i = 0; i < action_ids.size(); ++i) {
        query.bindValue(QString(":action_id%1").arg(i),action_ids.at(i));
    }
    if (!rarities.isEmpty()) {
        for (int i = 0; i < rarities.size(); ++i) {
            query.bindValue(QString(":rarity%1").arg(i),rarities.at(i));
        }
    }
    if (!types.isEmpty()) {
        for (int i = 0; i < types.size(); ++i) {
            query.bindValue(QString(":types%1").arg(i),types.at(i));
        }
    }
    if (query.exec()) {
        int id = query.record().indexOf("id");
        int idlvl = query.record().indexOf("lvl");
        while (query.next()) {
            res.push_back(QPair<int,int>(query.value(id).toInt(),query.value(idlvl).toInt()));
        }
    } else {
        qDebug() << query.lastError();
    }
    return  res;
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
