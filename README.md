Builder_Wakfu

Database setup commands : 

CREATE TABLE wakfu_builder.effect (id integer PRIMARY KEY, actionId integer,areaShape integer, areaSize text, params text, description text);
CREATE TABLE wakfu_builder.action (id integer PRIMARY KEY, description text, effect text);
CREATE TABLE wakfu_builder.itemproperties (id integer PRIMARY KEY, name text, description text);
CREATE TABLE wakfu_builder.equipmentItemType (id integer PRIMARY KEY, parentId integer, recyclable bool, visibleInAnimation bool, title text);
CREATE TABLE wakfu_builder.equipmentPosition (id integer PRIMARY KEY, name text);
CREATE TABLE wakfu_builder.eqpType_Pos_relation(id_ET integer, id_Pos integer, CONSTRAINT relation_pos_pk PRIMARY KEY(id_ET,id_Pos));
CREATE TABLE wakfu_builder.eqpType_DisPos_relation(id_ET integer, id_Pos integer, CONSTRAINT relation_disPos_pk PRIMARY KEY(id_ET,id_Pos));

CREATE TABLE wakfu_builder.item( id integer PRIMARY KEY, lvl integer, itemTypeId integer, itemSetId integer, rarity integer, bindType integer, minimumShardSlotNumber integer, maximumShardSlotNumber integer, useApCost integer, useMpCost integer, useWpCost integer, useMinRange integer, useMaxRange integer, useTestFreeCell bool, useTestLos bool, useTestOnlyLine bool, useTestNoBorderCell bool, useWorldTarget integer, gfxid integer, title text, description text);
CREATE TABLE wakfu_builder.item_properties_relation(id_item integer, id_property integer, CONSTRAINT relation_prop_pk PRIMARY KEY(id_item,id_property));
CREATE TABLE wakfu_builder.item_useEffect_relation(id_item integer, id_E integer, CONSTRAINT relation_uE_pk PRIMARY KEY(id_item,id_E));
CREATE TABLE wakfu_builder.item_useCriticalEffect_relation(id_item integer, id_E integer, CONSTRAINT relation_uCE_pk PRIMARY KEY(id_item,id_E));
CREATE TABLE wakfu_builder.item_useEquipEffect_relation(id_item integer, id_E integer, CONSTRAINT relation_uEE_pk PRIMARY KEY(id_item,id_E));

CREATE TABLE wakfu_builder.builder_save (id SERIAL UNIQUE, json text, name text, niveau integer);


delete from wakfu_builder.action;
delete from wakfu_builder.itemproperties;
delete from wakfu_builder.equipmentItemType;
delete from wakfu_builder.equipmentPosition;
delete from wakfu_builder.eqpType_Pos_relation;
delete from wakfu_builder.eqpType_DisPos_relation;

delete from wakfu_builder.effect;
delete from wakfu_builder.item;
delete from wakfu_builder.item_properties_relation;
delete from wakfu_builder.item_useEffect_relation;
delete from wakfu_builder.item_useCriticalEffect_relation;
delete from wakfu_builder.item_useEquipEffect_relation;
