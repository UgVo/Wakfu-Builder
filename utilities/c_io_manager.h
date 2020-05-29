#ifndef C_IO_MANAGER_H
#define C_IO_MANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "c_item.h"
#include "c_build.h"
#include "c_dbmanager.h"

class c_builder_view;

class c_io_manager : public QObject
{
    Q_OBJECT
public:
    enum jsonformat {file,database};

    explicit c_io_manager(c_dbmanager *_db_manager, QObject *parent = nullptr);

signals:

public slots:
    QJsonObject itemToJson(const c_item &item_view);
    QJsonObject builderToJson(const c_builder_view *builder);
    QByteArray save(const c_builder_view *builder, const c_io_manager::jsonformat format = c_io_manager::jsonformat::database, const QString path = QString());
    void jsonToBuilder(c_builder_view *builder, const QJsonObject &json);
    void load(c_builder_view *builder, const c_io_manager::jsonformat format, QString path = QString(), int id = 0);

private:
    c_dbmanager *db_manager;
};

#endif // C_IO_MANAGER_H
