#ifndef DIALOGGESTION_H
#define DIALOGGESTION_H

#include <QDialog>
#include <QDebug>
#include <QThread>
#include "utilities/c_datamanager.h"

namespace Ui {
class DialogGestion;
}

class ParseItemThread : public QThread
{
    Q_OBJECT
    void run() override {
        datamanager->parseItem();
        emit resultReady();
    }
    c_datamanager *datamanager;
signals:
    void resultReady();

public:
    void setDatamanager(c_datamanager *dtm) {
        datamanager = dtm;
    }
};

class DialogGestion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGestion(c_datamanager *data, QString ver = QString(), QWidget *parent = nullptr);
    ~DialogGestion();
    void setVersionText(QString);
    void setText(QString);

public slots:
    void slot_update_file();
    void slot_update_database();
    void slot_update_images();
    void slot_new_image(int index, int size);
    void slot_endUpdateImages();
    void slot_new_file(int index,int size);
    void slot_endUpdateFiles();
    void slot_new_item(QString ,int index, int size);
    void slot_endUpdateItems();

    void set_version(QString version);

private:
    Ui::DialogGestion *ui;
    c_datamanager *data_manager;
    QString version;
    ParseItemThread *parser;

signals:
    void updateItem(QWidget*);
};

#endif // DIALOGGESTION_H
