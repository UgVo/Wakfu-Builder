#include "c_item.h"
#include "c_dbmanager.h"

const QString c_item::FIRST_WEAPON = "FIRST_WEAPON";
const QString c_item::SECOND_WEAPON = "SECOND_WEAPON";
const QString c_item::LEFT_HAND = "LEFT_HAND";
const QString c_item::RIGHT_HAND = "RIGHT_HAND";
const QString c_item::LEGS = "LEGS";
const QString c_item::NECK = "NECK";
const QString c_item::BACK = "BACK";
const QString c_item::BELT = "BELT";
const QString c_item::HEAD = "HEAD";
const QString c_item::CHEST = "CHEST";
const QString c_item::SHOULDERS = "SHOULDERS";
const QString c_item::ACCESSORY = "ACCESSORY";
const QString c_item::PET = "PET";
const QString c_item::NONE = "NONE";

QMap<QString,int> c_item::mapTypeToId = c_item::init_mapTypeToId();
QMap<QString,int> c_item::mapRarityToId = c_item::init_mapRarityToId();
QMap<QString,int> c_item::mapCaracToId = c_item::init_mapCaracToId();
QMap<QString,int> c_item::mapFamilierSpeToLvl = c_item::ini_mapFamilierSpeToLvl();


c_item::c_item(int id, int lvl, QString name, QString description, c_equipmentItemTypes itemType,
               int itemSetId, int rarity, bool bindType, int minShNum,
               int maxShNum, int ApCost, int MpCost, int WpCost,
               int minRange, int maxRange, bool testFreeCell, bool testLos,
               bool testOnlyLine, bool testNoBorderCell, int worldTarget, int gfxId,
               QVector<c_itemProperties> properties, QVector<c_effect> useEffects,
               QVector<c_effect> useCriticalEffects, QVector<c_effect> equipEffects) {
    _id = id;
    _lvl = lvl;
    _name = name;
    _description = description;
    _itemType = itemType;
    _itemSetId = itemSetId;
    _rarity = rarity;
    _bindType = bindType;
    _minimumShardSlotNumber = minShNum;
    _maximumShardSlotNumber = maxShNum;
    _useApCost = ApCost;
    _useMpCost = MpCost;
    _useWpCost = WpCost;
    _useMinRange = minRange;
    _useMaxRange = maxRange;
    _useTestFreeCell = testFreeCell;
    _useTestLos = testLos;
    _useTestOnlyLine = testOnlyLine;
    _useTestNoBorderCell = testNoBorderCell;
    _useWorldTarget = worldTarget;
    _properties = properties;
    _useEffects = useEffects;
    _useCriticalEffects = useCriticalEffects;
    _equipEffects = equipEffects;
    _gfxId = gfxId;
    _number_element = 0;

    initBonuses();
}

c_item::c_item(QJsonObject object, c_dbmanager *dbManager) {
    QJsonObject definition = object.value(QString("definition")).toObject();
    QJsonObject item = definition.value(QString("item")).toObject();
    QJsonObject baseParameter = item.value(QString("baseParameters")).toObject();
    QJsonObject useParameter = item.value(QString("useParameters")).toObject();

    _id = item.value("id").toInt();
    _lvl =item.value("level").toInt();
    _itemType = dbManager->get_equipmentItemType(baseParameter.value(QString("itemTypeId")).toInt());
    _itemSetId = baseParameter.value(QString("itemSetId")).toInt();
    _rarity = baseParameter.value(QString("rarity")).toInt();
    _bindType = baseParameter.value(QString("bindType")).toInt();
    _minimumShardSlotNumber = baseParameter.value(QString("minimumShardSlotNumber")).toInt();
    _maximumShardSlotNumber = baseParameter.value(QString("maximumShardSlotNumber")).toInt();
    _useApCost = useParameter.value(QString("useCostAp")).toInt();
    _useMpCost = useParameter.value(QString("useCostMp")).toInt();
    _useWpCost = useParameter.value(QString("useCostWp")).toInt();
    _useMinRange = useParameter.value(QString("useRangeMin")).toInt();
    _useMaxRange = useParameter.value(QString("useRangeMax")).toInt();
    _useTestFreeCell = useParameter.value(QString("useTestFreeCell")).toBool();
    _useTestLos = useParameter.value(QString("useTestLos")).toBool();
    _useTestOnlyLine = useParameter.value(QString("useTestOnlyLine")).toBool();
    _useTestNoBorderCell = useParameter.value(QString("useTestNoBorderCell")).toBool();
    _useWorldTarget = useParameter.value(QString("useWorldTarget")).toInt();
    _gfxId = item.value(QString("graphicParameters")).toObject().value(QString("gfxId")).toInt();

    QJsonArray propArray = item.value(QString("properties")).toArray();
    for (QJsonArray::iterator it = propArray.begin(); it != propArray.end(); ++it ) {
        int id = it->toInt();
        _properties.push_back(dbManager->get_itemProperty(id));
    }

    QJsonArray useEffetArray = definition.value(QString("useEffects")).toArray();
    for (QJsonArray::iterator it = useEffetArray.begin(); it != useEffetArray.end(); ++it) {
        _useEffects.push_back(c_effect(it->toObject().value(QString("effect")).toObject(),dbManager));
    }

    QJsonArray useCriticalEffectsArray = definition.value(QString("useCriticalEffects")).toArray();
    for (QJsonArray::iterator it = useCriticalEffectsArray.begin(); it != useCriticalEffectsArray.end(); ++it) {
        _useCriticalEffects.push_back(c_effect(it->toObject().value(QString("effect")).toObject(),dbManager));
    }

    QJsonArray equipEffectsArray = definition.value(QString("equipEffects")).toArray();
    for (QJsonArray::iterator it = equipEffectsArray.begin(); it != equipEffectsArray.end(); ++it) {
        _equipEffects.push_back(c_effect(it->toObject().value(QString("effect")).toObject(),dbManager));
    }
    _name = object.value(QString("title")).toObject().value(QString("fr")).toString();
    _description = object.value(QString("description")).toObject().value(QString("fr")).toString();

    if (_itemType.getId() == 582) {
        if (mapFamilierSpeToLvl.contains(_name)) {
            _lvl = mapFamilierSpeToLvl[_name];
        } else {
            _lvl = 50;
        }
    }

    initBonuses();
    init_mapTypeToId();
}

QMap<QString,int> c_item::init_mapTypeToId() {
    QMap<QString,int> _mapTypeToId;
    _mapTypeToId.insertMulti("TWO_HAND_WEAPON",101);
    _mapTypeToId.insertMulti("RING",103);
    _mapTypeToId.insertMulti("ONE_HAND_WEAPON",108);
    _mapTypeToId.insertMulti("ONE_HAND_WEAPON",110);
    _mapTypeToId.insertMulti("TWO_HAND_WEAPON",111);
    _mapTypeToId.insertMulti("SECOND_HAND",112);
    _mapTypeToId.insertMulti("ONE_HAND_WEAPON",113);
    _mapTypeToId.insertMulti("TWO_HAND_WEAPON",114);
    _mapTypeToId.insertMulti("ONE_HAND_WEAPON",115);
    _mapTypeToId.insertMulti("TWO_HAND_WEAPON",117);
    _mapTypeToId.insertMulti("LEGS",119);
    _mapTypeToId.insertMulti("NECK",120);
    _mapTypeToId.insertMulti("BACK",132);
    _mapTypeToId.insertMulti("BELT",133);
    _mapTypeToId.insertMulti("HEAD",134);
    _mapTypeToId.insertMulti("CHEST",136);
    _mapTypeToId.insertMulti("SHOULDERS",138);
    _mapTypeToId.insertMulti("SECOND_HAND",189);
    _mapTypeToId.insertMulti("ONE_HAND_WEAPON",219);
    _mapTypeToId.insertMulti("TWO_HAND_WEAPON",223);
    _mapTypeToId.insertMulti("TWO_HAND_WEAPON",253);
    _mapTypeToId.insertMulti("ONE_HAND_WEAPON",254);
    _mapTypeToId.insertMulti("ACCESSORY",480);
    _mapTypeToId.insertMulti("ONE_HAND_WEAPON",518);
    _mapTypeToId.insertMulti("TWO_HAND_WEAPON",519);
    _mapTypeToId.insertMulti("SECOND_HAND",520);
    _mapTypeToId.insertMulti("ACCESSORY",537);
    _mapTypeToId.insertMulti("PET",582);
    _mapTypeToId.insertMulti("ACCESSORY",646);
    _mapTypeToId.insertMulti("COSTUME",647);
    return _mapTypeToId;
}

QMap<QString,int> c_item::init_mapRarityToId() {
    QMap<QString,int> _mapRarityToId;
    _mapRarityToId["Commun"] = 0;
    _mapRarityToId["Inhabituel"] = 1;
    _mapRarityToId["Rare"] = 2;
    _mapRarityToId["Mythique"] = 3;
    _mapRarityToId["Légendaire"] = 4;
    _mapRarityToId["Relique"] = 5;
    _mapRarityToId["Souvenir"] = 6;
    _mapRarityToId["Epique"] = 7;
    return _mapRarityToId;
}

QMap<QString,int> c_item::init_mapCaracToId() {
    QMap<QString,int> _mapCaracToId;
    _mapCaracToId = {
        {"Vie",21},
        {"PA",31},
        {"PM",41},
        {"PW",191},
        {"Parade",875},
        {"Coup Critique",150},
        {"Initiative",171},
        {"Portée",160},
        {"Esquive",175},
        {"Tacle",173},
        {"Sagesse",166},
        {"Prospection",162},
        {"Contrôle",184},
        {"Art du barda",234},
        {"Volonté",177},
        {"Maîtrise Élémentaire",120},
        {"Maîtrise Élémentaire Feu",122},
        {"Maîtrise Élémentaire Eau",123},
        {"Maîtrise Élémentaire Terre",124},
        {"Maîtrise Élémentaire Air",125},
        {"Maîtrise sur 1 éléments",1068},
        {"Maîtrise sur 2 éléments",1068},
        {"Maîtrise sur 3 éléments",1068},
        {"Maîtrise Critique",149},
        {"Maîtrise Dos",180},
        {"Maîtrise Distance",1053},
        {"Maîtrise Mêlée",1052},
        {"Maîtrise Monocible",1051},
        {"Maîtrise Zone",1050},
        {"Maîtrise Soin",26},
        {"Maîtrise Berserk",1055},
        {"Résistance Élémentaire",80},
        {"Résistance sur 1 éléments",1069},
        {"Résistance sur 2 éléments",1069},
        {"Résistance sur 3 éléments",1069},
        {"Résistance Critique",988},
        {"Résistance Dos",71},
        {"Niv. aux sorts Feu",832},
        {"Niv. aux sorts Eau",832},
        {"Niv. aux sorts Terre",832},
        {"Niv. aux sorts Air",832},
    };
    return  _mapCaracToId;
}


int c_item::getNumber_element() const
{
    return _number_element;
}

void c_item::setNumber_element(int value)
{
    _number_element = value;
}

QMap<QString, QString> c_item::getConstraints() const {
    return _constraints;
}

void c_item::setConstraints(const QMap<QString, QString> &constraints) {
    _constraints = constraints;
}

QList<QString> c_item::getElements(int number) const {
//    if (!number) {
//        return _elements;
//    } else {
        return _elements.mid(0,number);
//    }
}

void c_item::setElements(const QList<QString> &elements)
{
    _elements = elements;
}

int c_item::getId() const {
    return _id;
}

int c_item::getLvl() const {
    return _lvl;
}

QString c_item::getName() const {
    return _name;
}

QString c_item::getDescription() const {
    return _description;
}

c_equipmentItemTypes c_item::getType() const {
    return _itemType;
}

int c_item::getSetId() const {
    return _itemSetId;
}

int c_item::getRarity() const {
    return _rarity;
}

int c_item::getBindType() const {
    return _bindType;
}

int c_item::getMinShardNumber() const {
    return _minimumShardSlotNumber;
}

int c_item::getMaxShardNumber() const {
    return  _maximumShardSlotNumber;
}

int c_item::getApUseCost() const {
    return _useApCost;
}

int c_item::getMpUseCost() const {
    return  _useMpCost;
}

int c_item::getWpUseCost() const {
    return  _useWpCost;
}

int c_item::getMinRange() const {
    return  _useMinRange;
}

int c_item::getMaxRange() const {
    return  _useMaxRange;
}

bool c_item::TestFreeCell() const {
    return  _useTestFreeCell;
}

bool c_item::TestLos() const {
    return  _useTestLos;
}

bool c_item::TestOnlyLine() const {
    return  _useTestOnlyLine;
}

bool c_item::TestNoBorderCell() const {
    return _useTestNoBorderCell;
}

int c_item::useWorldTarget() const {
    return _useWorldTarget;
}

int c_item::getGfxId() const {
    return _gfxId;
}

QVector<c_itemProperties> c_item::getProperties() const {
    return _properties;
}

QVector<c_effect> c_item::getUseEffects() const {
    return _useEffects;
}

QVector<c_effect> c_item::getUseCriticalEffects()  const {
    return  _useCriticalEffects;
}

QVector<c_effect> c_item::getEquipEffects() const {
    return _equipEffects;
}

QStringList c_item::getEquipEffectsString() const {
    QStringList list;
    for (QVector<c_effect>::const_iterator it = _equipEffects.begin(); it != _equipEffects.end(); ++it) {
        list.append(it->getEffectString(_lvl).value("text"));
    }
    return list;
}

QStringList c_item::getUseEffectsString() const {
    QStringList list;
    for (QVector<c_effect>::const_iterator it = _useEffects.begin(); it != _useEffects.end(); ++it) {
        list.append(it->getEffectString(_lvl).value("text"));
    }
    return list;
}

QStringList c_item::getUseCriticalEffectsString() const {
    QStringList list;
    for (QVector<c_effect>::const_iterator it = _useCriticalEffects.begin(); it != _useCriticalEffects.end(); ++it) {
        list.append(it->getEffectString(_lvl).value("text"));
    }
    return list;
}

void c_item::setId(const int id) {
    _id = id;
}

void c_item::setLvl(const int lvl) {
    _lvl = lvl;
}

void c_item::setName(const QString name) {
    _name = name;
}

void c_item::setDescription(const QString description) {
    _description = description;
}

void c_item::setType(const c_equipmentItemTypes itemType) {
    _itemType = itemType;
}

void c_item::setSetId(const int setId) {
    _itemSetId = setId;
}

void c_item::setRarity(const int rarity) {
    _rarity = rarity;
}

void c_item::setBindType(const int bind) {
    _bindType = bind;
}

void c_item::setMinShardeNumber(const int min) {
    _minimumShardSlotNumber = min;
}

void c_item::setMaxShardNumber(const int max) {
    _maximumShardSlotNumber = max;
}

void c_item::setApUseCost(const int cost) {
    _useApCost = cost;
}

void c_item::setMpUseCost(const int cost) {
    _useMpCost = cost;
}

void c_item::setWpUseCost(const int cost) {
    _useWpCost = cost;
}

void c_item::setMinRange(const int range) {
    _useMinRange = range;
}

void c_item::setMaxRange(const int range) {
    _useMaxRange = range;
}

void c_item::setFreeCell(const bool flag) {
    _useTestFreeCell = flag;
}

void c_item::setLos(const bool flag) {
    _useTestLos = flag;
}

void c_item::setOnlyLine(const bool flag) {
    _useTestOnlyLine = flag;
}

void c_item::setNoBorderCell(const bool flag) {
    _useTestNoBorderCell = flag;
}

void c_item::setUseWorldTarget(const int target) {
    _useWorldTarget = target;
}

void c_item::setGfxId(const int id) {
    _gfxId = id;
}

void c_item::setProperties(const QVector<c_itemProperties> properties) {
    _properties = properties;
}

void c_item::setUseEffects(const QVector<c_effect> effects) {
    _useEffects = effects;
}

void c_item::setUseCriticalEffects(const QVector<c_effect> effects) {
    _useCriticalEffects = effects;
}

void c_item::setEquipEffets(const QVector<c_effect> effect) {
    _equipEffects = effect;
    initBonuses();
}

void c_item::initBonuses() {
    foreach (c_effect effect, _equipEffects) {
        QMap<QString,QString> map = effect.getEffectMap(_lvl);
        _bonuses[map["effect"]] = map["value"].toInt();
        if (map["effect"].contains("1")) {
            _number_element = 1;
        }
        if (map["effect"].contains("2")) {
            _number_element = 2;
        }
        if (map["effect"].contains("3")) {
            _number_element = 3;
        }
    }
}

QMap<QString, int> c_item::getBonuses() const {
    return _bonuses;
}

bool c_item::isEmpty() {
    return !_id;
}

QStringList c_item::position() {
    return {HEAD, NECK, BACK, SHOULDERS, CHEST, BELT,LEFT_HAND, RIGHT_HAND, LEGS, FIRST_WEAPON, SECOND_WEAPON, ACCESSORY, PET};
}

QMap<QString,int> c_item::ini_mapFamilierSpeToLvl() {
    return {{"Dot",25},{"Gélutin Aventurier",25},{"Gélutin Chasseur",25},{"Gélutin Combattant",25},{"Gélutin Berserker",25},{"Gélutin Soigneur",25},{"Tirubim",0}};
}
