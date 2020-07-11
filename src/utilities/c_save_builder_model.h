#ifndef C_SAVE_BUILDER_MODEL_H
#define C_SAVE_BUILDER_MODEL_H

#include <QAbstractTableModel>
#include <QSqlDatabase>
#include <QJsonDocument>
#include "c_dbmanager.h"

class struct_save{
public:
    int id;
    QString name;
    int lvl;
    QString json;
    QString image_url;
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
    bool removeRow(const QModelIndex);

    QString getJson(const QModelIndex index);
    int getId(const QModelIndex index);
    int getLvl(const QModelIndex index);
    QString getUrlImage(const QModelIndex index);
    QString getName(const QModelIndex index);

public slots:
    bool populate();

private:
     c_dbmanager *db_manager;
     QList<struct_save> data_list;

};

#endif // C_SAVE_BUILDER_MODEL_H
