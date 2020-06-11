#ifndef C_DATAMANAGER_H
#define C_DATAMANAGER_H

#include <utilities/utilities.h>
#include "c_dbmanager.h"
#include "c_networkmanager.h"
#include <QObject>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QTranslator>
#include <QMainWindow>
#include <QSet>
#include <QVariantMap>
#include <QJsonArray>
#include <QProgressDialog>

class c_datamanager : public QObject
{
    Q_OBJECT
public:
    c_datamanager();
    void checkVersion();
    void updateVersion(QString newVersion);
    void updateFiles();
    void parseActions();
    void setDBManager(c_dbmanager* dbmanager);
    void parseItemproperties();
    void parseEquipementItemType();
    void parseItem();
    QString getVersion();
    void getImages();
    void parseStates();
    QString getPassword();

private:
    QStringList _filelist;
    c_networkManager* networkManager;
    c_dbmanager* dbmanager;
    QString url_json;
    QString url_image;
    QString version_local;
    QString pathJson;
    QString pathImage;
    QString password;
    int index_fileList;
    QList<int> _imageList;
    int index_imageList;
    QString imageDir;

public slots:
    void slot_downloadVersionFinished(QString out);
    void slot_newVersion();
    void trigger_download_element();
    void trigger_download_images();

signals:
    void newVersion(QString);
    void newItem(QString name,int index, int size);
    void updateItemFinished();
    void newImage(int index, int size);
    void downloadImageFinished();
    void newFile(int index, int size);
    void downloadFileFinished();

};

#endif // C_DATAMANAGER_H
