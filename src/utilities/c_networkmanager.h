#ifndef C_NETWORKMANAGER_H
#define C_NETWORKMANAGER_H

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QProgressDialog>
#include <QUrl>

class c_networkManager : public QObject {
    Q_OBJECT
   public:
    explicit c_networkManager(QObject *parent = nullptr);
    void downloadFile(QUrl url, QString path);

   public slots:
    void updateDownloadProgress(qint64 bytesRead, qint64 totalBytes);
    void httpDataReceived();
    void httpDownloadFinished();
    void startRequest(QUrl url);
    void cancelDownload();

   signals:
    void downloadFinished(QString out);

   private:
    QFile *file;
    QString lastVersion;
    QString content;

    QUrl url;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    bool httpRequestAborted;
    QProgressDialog *progressDialog;
    qint64 fileSize;
};

#endif  // C_NETWORKMANAGER_H
