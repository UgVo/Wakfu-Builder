#include "c_save_builder_model.h"

c_save_builder_model::c_save_builder_model(c_dbmanager *manager, QObject *parent)
    : QAbstractTableModel(parent) {
    m_db = manager->getDb();
    data_list = QList<struct_save>();
    populate();
    qDebug() << data_list.size();

}

QVariant c_save_builder_model::headerData(int section, Qt::Orientation orientation, int role) const
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
            default:
                break;
            }
        }
    }
    return QVariant();
}

int c_save_builder_model::rowCount(const QModelIndex& /*&parent*/) const {
    return data_list.size();
}

int c_save_builder_model::columnCount(const QModelIndex&/* &parent*/) const {
    return 3;
    // FIXME: Implement me!
}

QVariant c_save_builder_model::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            switch (index.column()) {
                case 0:
                    return data_list.at(index.row()).id;
                case 1:
                    return data_list.at(index.row()).lvl;
                case 2:
                    return data_list.at(index.row()).name;
                default:
                    break;
            }
    }
    return QVariant();
}

bool c_save_builder_model::insertRow(struct_save save) {
    beginInsertRows(QModelIndex(), data_list.size(),data_list.size());
    qDebug() << save.id << save.name;
    data_list.push_back(save);
    endInsertRows();
    return true;
}

bool c_save_builder_model::populate() {
    QSqlQuery query(m_db);
    struct_save save;
    query.prepare("SELECT * FROM wakfu_builder.builder_save");
    if (query.exec()) {
        int id = query.record().indexOf("id");
        int idLvl = query.record().indexOf("niveau");
        int idName = query.record().indexOf("name");
        int idjson = query.record().indexOf("json");
        qDebug() << query.record();
        while (query.next()) {
            save.id = query.value(id).toInt();
            save.lvl = query.value(idLvl).toInt();
            save.name = query.value(idName).toString();
            save.json = query.value(idjson).toString();
            qDebug() << save.json;
            insertRow(save);
        }
        return true;
    } else {
        qDebug() << query.lastError();
        return false;
    }
}

QString c_save_builder_model::getJson(const QModelIndex index) {
    return data_list.at(index.row()).json;
}

int c_save_builder_model::getId(const QModelIndex index) {
    return data_list.at(index.row()).id;
}
