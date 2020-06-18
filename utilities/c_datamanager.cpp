#include "c_datamanager.h"

c_datamanager::c_datamanager()
{
    dbmanager = nullptr;
    networkManager = new c_networkManager();

#ifdef Q_OS_MACX
    imageDir = QCoreApplication::applicationDirPath() + "/../Resources";
#else
    imageDir = QCoreApplication::applicationDirPath();
#endif

    QString val;
    QFile file;
    QString version;
    QJsonDocument doc;
    QJsonObject jObject_config;
    QJsonObject jObject_version;
    QJsonObject JObject_nameList;

    file.setFileName("config.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        c_bdd_password_dialog dial;
        QString password;
        if (dial.exec() == QDialog::Accepted) {
            password = dial.get_password();
        }
        val = QString("{"
                  "\"version\" : \"1.68.0.179615\","
                  "\"url_json\" : \"https://wakfu.cdn.ankama.com/gamedata/\","
                  "\"url_image\" : \"https://static.ankama.com/wakfu/portal/game/item/64/\","
                  "\"path_json\" : \"json\","
                  "\"path_images\" : \"images/Items\","
                  "\"filelist\" : { "
                      "\"1\": \"items.json\","
                      "\"2\": \"equipmentItemTypes.json\","
                      "\"3\": \"itemProperties.json\","
                      "\"4\": \"actions.json\","
                      "\"5\": \"states.json\","
                      "\"6\": \"jobsItems.json\""
                  "},"
                  "\"password\" : \"%1\""
              "}").arg(password);
        file.write(val.toUtf8());
    } else {
        val = file.readAll();
    }
    file.close();
    doc = QJsonDocument::fromJson(val.toUtf8());
    jObject_config = doc.object();
    pathJson = jObject_config.value(QString("path_json")).toString();
    version_local = jObject_config.value((QString("version"))).toString();
    url_json = jObject_config.value(QString("url_json")).toString();
    url_image = jObject_config.value(QString("url_image")).toString();
    pathImage = jObject_config.value(QString("path_images")).toString();
    password = jObject_config.value(QString("password")).toString();

    JObject_nameList = jObject_config.value(QString("filelist")).toObject();
    for(int i = 0; i < JObject_nameList.size(); ++i) {
        _filelist.push_back(JObject_nameList.value(QString("%1").arg(i+1)).toString());
    }
}

void c_datamanager::checkVersion() {
    if (networkManager != nullptr) {
        QObject::disconnect(networkManager,SIGNAL(downloadFinished(QString)),this,SLOT(trigger_download_images()));
        networkManager->deleteLater();
        networkManager = nullptr;
    }
    networkManager =  new c_networkManager();
    networkManager->downloadFile(QUrl(url_json + "config.json"),pathJson);
    QObject::connect(networkManager,SIGNAL(downloadFinished(QString)),this,SLOT(slot_downloadVersionFinished(QString)));
}

void c_datamanager::updateVersion(QString newVersion) {
    QFile file;
    QJsonDocument doc;
    QString val;
    file.setFileName("config.json");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    val = file.readAll();
    val = val.replace(version_local,newVersion);
    file.resize(0);
    file.write(val.toUtf8());
    version_local = newVersion;
    return;
}

void c_datamanager::updateFiles() {
    index_fileList = 0;
    trigger_download_element();
}

void c_datamanager::slot_downloadVersionFinished(QString out) {
    QObject::disconnect(networkManager,SIGNAL(downloadFinished(QString)),this,SLOT(slot_downloadVersionFinished(QString)));
    QString version;
    QJsonDocument doc;

    doc = QJsonDocument::fromJson(out.toUtf8());
    version = doc.object().value(QString("version")).toString();
    emit newVersion(version);
}

void c_datamanager::slot_newVersion() {
    QObject::disconnect(this,SIGNAL(newVersion()),this,SLOT(slot_newVersion()));
    index_fileList = 0;
    trigger_download_element();
}

void c_datamanager::trigger_download_element() {
    if (networkManager != nullptr) {
        QObject::disconnect(networkManager,SIGNAL(downloadFinished(QString)),this,SLOT(trigger_download_element()));
        networkManager->deleteLater();
        networkManager = nullptr;
    }
    if (index_fileList < _filelist.size()) {
        networkManager = new c_networkManager();
        QObject::connect(networkManager,SIGNAL(downloadFinished(QString)),this,SLOT(trigger_download_element()));
        networkManager->downloadFile(url_json+version_local+"/"+ _filelist.at(index_fileList++),pathJson);
        emit newFile(index_fileList,_filelist.size());
    } else {
        emit downloadFileFinished();
        qInfo() << "All files have been downloaded";
    }
}

void c_datamanager::parseActions() {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonArray JsonArray;
    file.setFileName(pathJson + "/actions.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    doc = QJsonDocument::fromJson(val.toUtf8());
    JsonArray = doc.array();
    for (QJsonArray::iterator it = JsonArray.begin(); it != JsonArray.end(); ++it) {
        c_action value_action(it->toObject());
        qWarning() << dbmanager->add_action(value_action);
    }
}

void c_datamanager::setDBManager(c_dbmanager* _dbmanager) {
    dbmanager = _dbmanager;
}

void c_datamanager::parseItemproperties() {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonArray JsonArray;
    file.setFileName(pathJson + "/itemProperties.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    doc = QJsonDocument::fromJson(val.toUtf8());
    JsonArray = doc.array();
    for (QJsonArray::iterator it = JsonArray.begin(); it != JsonArray.end(); ++it) {
        c_itemProperties itemProperty(it->toObject());
        qWarning() << dbmanager->add_itemProperty(itemProperty);
    }
}

void c_datamanager::parseEquipementItemType() {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonArray JsonArray;
    file.setFileName(pathJson + "/equipmentItemTypes.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    doc = QJsonDocument::fromJson(val.toUtf8());
    JsonArray = doc.array();
    for (QJsonArray::iterator it = JsonArray.begin(); it != JsonArray.end(); ++it) {
        c_equipmentItemTypes itemType(it->toObject());
        qWarning() << dbmanager->add_equipmentItemType(itemType);
    }
}

void c_datamanager::parseItem() {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonArray JsonArray;
    file.setFileName(pathJson + QString("/items.json"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    doc = QJsonDocument::fromJson(val.toUtf8());
    JsonArray = doc.array();
    QList<int> idList = dbmanager->getItemListId();
    for (QJsonArray::iterator it = JsonArray.begin(); it != JsonArray.end(); ++it) {
        c_item item(it->toObject(),dbmanager);
        emit newItem(item.getName(),it - JsonArray.begin(), JsonArray.size());
        if (!idList.contains(item.getId())) {
            dbmanager->add_item(item);
        } else {
            //qInfo() << item.getName() << " : Already in Database";
        }
    }
    emit updateItemFinished();
}

QString c_datamanager::getVersion() {
    return version_local;
}

void c_datamanager::getImages() {
    QDir directory(imageDir + "/images/items");
    QStringList images = directory.entryList(QStringList() << "*.png",QDir::Files);
    QList<int> images_id;

    foreach (QString id, images) {
        images_id.push_back(id.replace(".png","").toInt());
    }
    _imageList = dbmanager->getImagesList().toSet().subtract(images_id.toSet()).toList();
    index_imageList = 0;

    trigger_download_images();
}

void c_datamanager::trigger_download_images() {
    if (networkManager != nullptr) {
        QObject::disconnect(networkManager,SIGNAL(downloadFinished(QString)),this,SLOT(trigger_download_images()));
        networkManager->deleteLater();
        networkManager = nullptr;
    }
    if (index_imageList < _imageList.size()) {
        networkManager = new c_networkManager();
        QObject::connect(networkManager,SIGNAL(downloadFinished(QString)),this,SLOT(trigger_download_images()));
        QString url = url_image + QString("%1.png").arg(_imageList.at(index_imageList++));
        networkManager->downloadFile(url,pathImage);
        emit newImage(index_imageList,  _imageList.size());
    } else {
        qWarning() << "All files have been downloaded";
        emit downloadImageFinished();
    }
}

void c_datamanager::savePassword(QString _password) {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonObject jObject_config;

    file.setFileName("config.json");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    val = file.readAll();
    doc = QJsonDocument::fromJson(val.toUtf8());
    jObject_config = doc.object();
    jObject_config["password"] = _password;
    doc.setObject(jObject_config);
    file.resize(0);
    file.write(doc.toJson());
    file.close();
    password = _password;
    return;
}

void c_datamanager::parseStates() {
    QFile file;
    QJsonDocument doc;
    QString val;
    QJsonArray JsonArray;
    file.setFileName(pathJson + QString("/states.json"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    doc = QJsonDocument::fromJson(val.toUtf8());
    JsonArray = doc.array();
    QString description;
    for (QJsonArray::iterator it = JsonArray.begin(); it != JsonArray.end(); ++it) {
        c_state state(it->toObject());
        dbmanager->add_state(state);
    }
}

QString c_datamanager::getPassword() {
    return password;
}

