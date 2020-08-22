#include "c_networkmanager.h"

c_networkManager::c_networkManager(QObject *parent) : QObject(parent), file(nullptr), progressDialog(nullptr)  {}

void c_networkManager::downloadFile(QUrl url, QString path) {
    progressDialog = new QProgressDialog(nullptr);
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
    manager = new QNetworkAccessManager(this);

    QFileInfo fileInfo(url.path());
    QString fileName = path + "/" + fileInfo.fileName();

    if (fileName.isEmpty()) {
        return;
    }

    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }

    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadWrite)) {
        QMessageBox::information(nullptr, tr("HTTP"),
                      tr("Unable to save the file %1: %2.")
                      .arg(fileName).arg(file->errorString()));
        delete file;
        file = nullptr;
        progressDialog->deleteLater();
        emit downloadFinished(QString());
        return;
    }

    httpRequestAborted = false;

    progressDialog->setWindowTitle(tr("HTTP"));
    progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));

    startRequest(url);
}

void c_networkManager::startRequest(QUrl url)
{
    qDebug() << "Trying to download file at url: " << url;
    reply = manager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpDataReceived()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDownloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpDownloadFinished()));
}

void c_networkManager::httpDataReceived() {
    if (file) {
        QByteArray received =  reply->readAll();
        file->write(received);
        content.append(received);
    }
}

void c_networkManager::cancelDownload()
{
    httpRequestAborted = true;
    reply->abort();
}

void c_networkManager::updateDownloadProgress(qint64 bytesRead, qint64 totalBytes)
{
    if (httpRequestAborted)
        return;
    progressDialog->setMaximum(int(totalBytes));
    progressDialog->setValue(int(bytesRead));
}

void c_networkManager::httpDownloadFinished() {
    progressDialog->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply = nullptr;
    delete file;
    file = nullptr;
    manager = nullptr;
    progressDialog->deleteLater();
    progressDialog = nullptr;
    emit downloadFinished(content);
}
