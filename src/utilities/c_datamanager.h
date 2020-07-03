#ifndef C_DATAMANAGER_H
#define C_DATAMANAGER_H

#include <utilities/utilities.h>
#include "c_dbmanager.h"
#include "c_networkmanager.h"
#include "ui/c_bdd_password_dialog.h"
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
#include <QCoreApplication>
#include <QXmlStreamReader>

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
    void parseFinal();
    bool isNewSoftVersion();

private:
    QStringList _filelist;
    c_networkManager* networkManager;
    c_dbmanager* dbmanager;
    QString url_json;
    QString url_image;
    QString url_soft_vers;
    QString version_local;
    QString pathJson;
    QString pathImage;
    QString password;
    int index_fileList;
    QList<int> _imageList;
    int index_imageList;
    QString imageDir;
    QString soft_version;

    QList<int> id_non_final_list;
    bool new_soft_version;

    bool stop;

public slots:
    void slot_downloadVersionFinished(QString out);
    void slot_newVersion();
    void trigger_download_element();
    void trigger_download_images(QString out =  QString());
    void savePassword(QString password);
    void slot_check_softVersion(QString);
    void slot_stop();
    void empty_db();

signals:
    void newVersion(QString);
    void newItem(QString name,int index, int size);
    void updateItemFinished();
    void newImage(int index, int size);
    void downloadImageFinished();
    void newFile(int index, int size);
    void downloadFileFinished();
    void update_soft_version();

};

#endif // C_DATAMANAGER_H
