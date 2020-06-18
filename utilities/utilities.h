#ifndef UTILITIES_H
#define UTILITIES_H

#include "utilities/c_action.h"
#include "utilities/c_build.h"
#include "utilities/c_calcul.h"
#include "utilities/c_datamanager.h"
#include "utilities/c_dbmanager.h"
#include "utilities/c_effect.h"
#include "utilities/c_equipmentitemtypes.h"
#include "utilities/c_item.h"
#include "utilities/c_item_model.h"
#include "utilities/c_itemproperties.h"
#include "utilities/c_networkmanager.h"
#include "utilities/c_state.h"
#include "utilities/c_tokenizer.h"

#include <QObject>
#include <QString>
#include <QStringList>

const QMap<QString,QString> mapItemToType{
    {"Hache","TWO_HAND_WEAPON"},
    {"Anneau","RING"},
    {"Baguette","ONE_HAND_WEAPON"},
    {"Epée","ONE_HAND_WEAPON"},
    {"Pelle","TWO_HAND_WEAPON"},
    {"Dague","SECOND_HAND"},
    {"Bâton","ONE_HAND_WEAPON"},
    {"Marteau","TWO_HAND_WEAPON"},
    {"Aiguille","ONE_HAND_WEAPON"},
    {"Arc","TWO_HAND_WEAPON"},
    {"Bottes","LEGS"},
    {"Amulette","NECK"},
    {"Cape","BACK"},
    {"Ceinture","BELT"},
    {"Casque","HEAD"},
    {"Plastron","CHEST"},
    {"Epaulettes","SHOULDERS"},
    {"Bouclier","SECOND_HAND"},
    {"Poing","ONE_HAND_WEAPON"},
    {"Epée à 2 mains","TWO_HAND_WEAPON"},
    {"Bâton à 2 mains","TWO_HAND_WEAPON"},
    {"Cartes","ONE_HAND_WEAPON"},
    {"Torches","ACCESSORY"},
    {"Armes 1 Main","ONE_HAND_WEAPON"},
    {"Armes 2 Mains","TWO_HAND_WEAPON"},
    {"Seconde Main","SECOND_HAND"},
    {"Outils","ACCESSORY"},
    {"Familiers","PET"},
    {"Emblème","ACCESSORY"},
    {"Costumes","COSTUME"},
    {"Montures","MOUNT"}};

const QMap<QString,QString> mapTypeToItem{
    {"TWO_HAND_WEAPON","Hache"},
    {"RING","Anneau"},
    {"ONE_HAND_WEAPON","Baguette"},
    {"ONE_HAND_WEAPON","Epée"},
    {"TWO_HAND_WEAPON","Pelle"},
    {"SECOND_HAND","Dague"},
    {"ONE_HAND_WEAPON","Bâton"},
    {"TWO_HAND_WEAPON","Marteau"},
    {"ONE_HAND_WEAPON","Aiguille"},
    {"TWO_HAND_WEAPON","Arc"},
    {"LEGS","Bottes"},
    {"NECK","Amulette"},
    {"BACK","Cape"},
    {"BELT","Ceinture"},
    {"HEAD","Casque"},
    {"CHEST","Plastron"},
    {"SHOULDERS","Epaulettes"},
    {"SECOND_HAND","Bouclier"},
    {"ONE_HAND_WEAPON","Poing"},
    {"TWO_HAND_WEAPON","Epée à 2 mains"},
    {"TWO_HAND_WEAPON","Bâton à 2 mains"},
    {"ONE_HAND_WEAPON","Cartes"},
    {"ACCESSORY","Torches"},
    {"ONE_HAND_WEAPON","Armes 1 Main"},
    {"TWO_HAND_WEAPON","Armes 2 Mains"},
    {"SECOND_HAND","Seconde Main"},
    {"ACCESSORY","Outils"},
    {"PET,","Familiers"},
    {"ACCESSORY","Emblème"},
    {"COSTUME","Costumes"}};

const QMap<QString,int> mapCaracToId {
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

#endif // UTILITIES_H
