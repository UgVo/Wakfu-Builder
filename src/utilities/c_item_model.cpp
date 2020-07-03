#include "c_item_model.h"

c_item_model::c_item_model(c_dbmanager *_manager,QObject *parent)
    : QAbstractTableModel(parent) {
    manager = _manager;
    qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");
}

void c_item_model::init() {
    int index = 0;
    QList<c_item> item_list = manager->getAllItem();
    for (QList<c_item>::iterator it = item_list.begin(); it != item_list.end(); ++it) {
        insert_row(*it);
        if ((it - item_list.begin())/100 > index) {
            emit new_row(it - item_list.begin(), item_list.size());
            index++;
        }

    }
    emit new_row(item_list.size()-1,item_list.size());
}

QVariant c_item_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return tr("Id");
            case 1:
                return tr("Niveau");
            case 2:
                return tr("Nom");
            case 3:
                return tr("Description");
            case 4:
                return tr("Type d'item");
            case 5:
                return tr("Id Panoplie");
            case 6:
                return tr("Rareté");
            case 7:
                return tr("Lié");
            case 8:
                return tr("Coût PA");
            case 9:
                return tr("Coût PM");
            case 10:
                return tr("Coût PW");
            case 11:
                return tr("Portée");
            default:
                break;
            }
        }
    }
    return QVariant();
}

int c_item_model::rowCount(const QModelIndex &/*parent*/) const
{
    return data_list.size();
}

int c_item_model::columnCount(const QModelIndex &/*parent*/) const
{
    return 12;
}

QVariant c_item_model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const c_item &item = data_list.at(index.row());
    switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            switch (index.column()) {
                case 0:
                    return data_list.at(index.row()).getId();
                case 1:
                    return data_list.at(index.row()).getLvl();
                case 2:
                    return data_list.at(index.row()).getName();
                case 3:
                    return data_list.at(index.row()).getDescription();
                case 4:
                    return data_list.at(index.row()).getType().getTitle();
                case 5:
                    return data_list.at(index.row()).getSetId();
                case 6:
                    return data_list.at(index.row()).getRarity();
                case 7:
                    return data_list.at(index.row()).getBindType();
                case 8:
                    return data_list.at(index.row()).getApUseCost();
                case 9:
                    return data_list.at(index.row()).getMpUseCost();
                case 10:
                    return data_list.at(index.row()).getWpUseCost();
                case 11:
                    return QString("%1 - %2").arg(item.getMinRange()).arg(item.getMaxRange());
                default:
                    break;
            }
    }
    return QVariant();
}

bool c_item_model::insert_row(c_item &item) {
    beginInsertRows(QModelIndex(), data_list.size(),data_list.size());
    data_list.push_back(item);
    data_map[item.getId()] = item;
    endInsertRows();
    return true;
}

c_item c_item_model::itemFromId(int id) {
    return c_item();
}
