#ifndef C_ITEM_MODEL_H
#define C_ITEM_MODEL_H

#include "c_dbmanager.h"
#include "c_item.h"
#include <QAbstractTableModel>
#include <QList>
#include <QEventLoop>
#include <QThread>

class c_item_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit c_item_model(c_dbmanager *_manager,QObject *parent = nullptr);
    void init();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool insert_row(c_item &item);
    c_item itemFromId(int id);

signals:
    void new_row(int index, int size);

private:
    c_dbmanager *manager;
    QList<c_item> data_list;
    QMap<int,c_item> data_map;
};

#endif // C_ITEM_MODEL_H
