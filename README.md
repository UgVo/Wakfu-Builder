Builder_Wakfu

Download from the lastest version of Posgresql (12.3) at: 
	https://www.enterprisedb.com/downloads/postgres-postgresql-downloads
	
Run pgAdmin (will open a web browser to access posgresql admin interface)
	The Master password and the password to access the PostgreSQL 12 Server are the same
	
	Create a new user wakfu_builder:
		Right click on 'Login/Group Roles'
			Create >
			Login/Group Role...
		In General tab Set the name wakfu_builder
		In Privileges set 'Can login?', 'Inherits rigths from the parent roles' and 'can initiate streaming replication and backup' to 'Yes'
		In Membership add 'postgres' in the Roles list
		Save
			
	Add a new Schemas and name it wakfu_builder
		Set the Owner to 'postgres' (default choice)
		In 'Security' tab, add 'postgres' and 'wakfu_builder' as Grantee with all the privileges
		Save

Run Sql Shell (psql)
	leave all identification default option and entre your password
	run the following commands :

	CREATE TABLE wakfu_builder.carac (id integer PRIMARY KEY, effect text, value integer);
	CREATE TABLE wakfu_builder.effect (id integer PRIMARY KEY, actionId integer,areaShape integer, areaSize text, params text, description text);
	CREATE TABLE wakfu_builder.action (id integer PRIMARY KEY, description text, effect text);
	CREATE TABLE wakfu_builder.itemproperties (id integer PRIMARY KEY, name text, description text);
	CREATE TABLE wakfu_builder.equipmentItemType (id integer PRIMARY KEY, parentId integer, recyclable bool, visibleInAnimation bool, title text);
	CREATE TABLE wakfu_builder.equipmentPosition (id integer PRIMARY KEY, name text);
	CREATE TABLE wakfu_builder.eqpType_Pos_relation(id_ET integer, id_Pos integer, CONSTRAINT relation_pos_pk PRIMARY KEY(id_ET,id_Pos));
	CREATE TABLE wakfu_builder.eqpType_DisPos_relation(id_ET integer, id_Pos integer, CONSTRAINT relation_disPos_pk PRIMARY KEY(id_ET,id_Pos));

	CREATE TABLE wakfu_builder.item( id integer PRIMARY KEY, lvl integer, itemTypeId integer, itemSetId integer, rarity integer, bindType integer, minimumShardSlotNumber integer, maximumShardSlotNumber integer, useApCost integer, useMpCost integer, useWpCost integer, useMinRange integer, useMaxRange integer, useTestFreeCell bool, useTestLos bool, useTestOnlyLine bool, useTestNoBorderCell bool, useWorldTarget integer, gfxid integer, title text, description text, isFinal bool);
	CREATE TABLE wakfu_builder.relation_item_carac( id_item integer, id_carac integer, FOREIGN KEY(id_item) REFERENCES wakfu_builder.item (id),FOREIGN KEY(id_carac) REFERENCES wakfu_builder.carac);
	CREATE TABLE wakfu_builder.item_properties_relation(id_item integer, id_property integer, CONSTRAINT relation_prop_pk PRIMARY KEY(id_item,id_property));
	CREATE TABLE wakfu_builder.item_useEffect_relation(id_item integer, id_E integer, CONSTRAINT relation_uE_pk PRIMARY KEY(id_item,id_E));
	CREATE TABLE wakfu_builder.item_useCriticalEffect_relation(id_item integer, id_E integer, CONSTRAINT relation_uCE_pk PRIMARY KEY(id_item,id_E));
	CREATE TABLE wakfu_builder.item_useEquipEffect_relation(id_item integer, id_E integer, CONSTRAINT relation_uEE_pk PRIMARY KEY(id_item,id_E));

	CREATE TABLE wakfu_builder.builder_save (id SERIAL UNIQUE, json text, name text, niveau integer);

	ALTER USER wakfu_builder password 'your_password';

Set up in the config.json file the corresponding password 'your_password'

The application should now be runable, the only thing left is to fill up the database using the tool in the application.
Go to Gestion, and then click on 'check new version' and then update the files, the database and finaly the images.

The application is now READY !

For reseting the database datas, run the following commands in Sql Shell (psql):

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
	delete from wakfu_builder.carac;
	
To compile your own version : 

	Add to the compilation PATH : 
		For OpenSSL :
	PATH_TO_QT_DIR\Tools\OpenSSL\Win_x64\bin;
		For POSGRESQL :
	PATH_TO_POSTGRESQL_DIR\bin;
	PATH_TO_POSTGRESQL_DIR\lib;
		For Windows kits :
	C:\Program Files (x86)\Windows Kits\10\bin\10.0.17134.0\x64
