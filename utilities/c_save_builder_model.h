#ifndef C_SAVE_BUILDER_MODEL_H
#define C_SAVE_BUILDER_MODEL_H

#include <QAbstractTableModel>
#include <QSqlDatabase>
#include "c_dbmanager.h"

class struct_save{
public:
    int id;
    QString name;
    int lvl;
    QString json;
};

class c_save_builder_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit c_save_builder_model(c_dbmanager* manager, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual int rowCount(const QModelIndex& ) const;
    virtual int columnCount(const QModelIndex& ) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRow(struct_save save);

    bool populate();
    QString getJson(const QModelIndex index);
    int getId(const QModelIndex index);

private:
     QSqlDatabase m_db;
     QList<struct_save> data_list;

};

#endif // C_SAVE_BUILDER_MODEL_H
