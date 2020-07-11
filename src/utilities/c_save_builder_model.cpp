#include "c_save_builder_model.h"

c_save_builder_model::c_save_builder_model(c_dbmanager *manager, QObject *parent)
    : QAbstractTableModel(parent) {
    db_manager = manager;
    data_list = QList<struct_save>();
    populate();
    QObject::connect(db_manager,&c_dbmanager::signal_new_save,this,&c_save_builder_model::populate);
}

QVariant c_save_builder_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return tr("");
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
    return 4;
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
                    return QVariant();
                case 1:
                    return data_list.at(index.row()).lvl;
                case 2:
                    return data_list.at(index.row()).name;
                default:
                    break;
            }
            break;
        case Qt::DecorationRole:
            if(index.column() == 0) return QPixmap(data_list[index.row()].image_url);
            return QVariant();
        case Qt::SizeHintRole:
            if(index.column() == 0) return QSize(20,20);
            break;
        case Qt::TextAlignmentRole:
            if (index.column() == 1) {
                return Qt::AlignCenter;
            } else {
                return QVariant();
            }
        case Qt::ForegroundRole:
            return QColor("white");
        break;
    }
    return QVariant();
}

bool c_save_builder_model::insertRow(struct_save save) {
    beginInsertRows(QModelIndex(), data_list.size(),data_list.size());
    data_list.push_back(save);
    endInsertRows();
    return true;
}

bool c_save_builder_model::removeRow(const QModelIndex index) {
    beginInsertRows(QModelIndex(), index.row(),index.row());
    db_manager->remove_builder(data_list[index.row()].id);
    data_list.removeAt(index.row());
    endInsertRows();
    return true;
}

bool c_save_builder_model::populate() {
    qDebug() << "populate";
    QSqlQuery query(db_manager->getDb());
    struct_save save;
    QJsonDocument doc;
    beginInsertRows(QModelIndex(),0,data_list.size()-1);
    data_list.clear();
    endInsertRows();
//    for (int i = 0; i < data_list.size(); ++i) {
//        removeRow(index(0,0));
//    }
    query.prepare("SELECT * FROM wakfu_builder.builder_save");
    if (query.exec()) {
        int id = query.record().indexOf("id");
        int idLvl = query.record().indexOf("niveau");
        int idName = query.record().indexOf("name");
        int idjson = query.record().indexOf("json");
        while (query.next()) {
            save.id = query.value(id).toInt();
            save.lvl = query.value(idLvl).toInt();
            save.name = query.value(idName).toString();
            save.json = query.value(idjson).toString();
            doc = QJsonDocument::fromJson(save.json.toUtf8());
            if (doc.object().contains("classe")) {
                int id = doc.object().value("classe").toInt();
                if (id) {
                    save.image_url = QString(":/images/portrait/small_%1.png").arg(id);
                } else {
                    save.image_url = QString(":/images/portrait/small_aleat.png");
                }
            } else  {
                save.image_url = QString(":/images/portrait/small_aleat.png");
            }
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

int c_save_builder_model::getLvl(const QModelIndex index) {
    return  data_list[index.row()].lvl;
}

QString c_save_builder_model::getUrlImage(const QModelIndex index) {
    QString res = data_list[index.row()].image_url;
    res.replace("small_","");
    return res;
}

QString c_save_builder_model::getName(const QModelIndex index) {
    return data_list[index.row()].name;
}
