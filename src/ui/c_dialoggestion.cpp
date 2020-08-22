#include "c_dialoggestion.h"
#include "ui_c_dialoggestion.h"

DialogGestion::DialogGestion(c_datamanager *data, QString ver, QWidget *parent) :
    QDialog(parent), ui(new Ui::DialogGestion), data_manager(data), version(ver)
{
    ui->setupUi(this);
    connect(ui->pb_update_files,&QPushButton::clicked,this,&DialogGestion::slot_update_file);
    connect(ui->pb_update_data_base,&QPushButton::clicked,this,&DialogGestion::slot_update_database);
    connect(ui->pb_update_images,&QPushButton::clicked,this,&DialogGestion::slot_update_images);
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(slot_on_close()));
    QString version_file = data_manager->getVersion();
    if (version_file == version) {
        ui->textBrowser->append(QString("Actual version of files up to date %1 \nUpdate files button disabled").arg(version));
    }
    ui->progressBar->setValue(0);
}

DialogGestion::~DialogGestion() {
    delete ui;
}

void DialogGestion::setVersionText(QString textVer) {
    ui->label_version->setText(textVer);
}

void DialogGestion::slot_update_file() {
    QString version_file = data_manager->getVersion();
    if (version_file == version) {
          qWarning() << "Files are already up to date dumb ass !";
    }
    connect(data_manager,&c_datamanager::newFile,this,&DialogGestion::slot_new_file);
    connect(data_manager,&c_datamanager::downloadFileFinished,this,&DialogGestion::slot_endUpdateFiles);
    ui->progressBar->setValue(0);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    ui->pb_update_files->setEnabled(false);
    ui->pb_update_data_base->setEnabled(false);
    ui->pb_update_images->setEnabled(false);
    data_manager->updateVersion(version);
    data_manager->updateFiles();
    ui->label_version->setText(version);
}

void DialogGestion::slot_new_file(int index,int size) {
    ui->progressBar->setMaximum(size);
    ui->progressBar->setValue(index+1);
}

void DialogGestion::slot_endUpdateFiles() {
    connect(data_manager,&c_datamanager::newFile,this,&DialogGestion::slot_new_file);
    connect(data_manager,&c_datamanager::downloadFileFinished,this,&DialogGestion::slot_endUpdateFiles);
    ui->progressBar->setValue(ui->progressBar->maximum());
    ui->pb_update_files->setEnabled(true);
    ui->pb_update_data_base->setEnabled(true);
    ui->pb_update_images->setEnabled(true);
}

void DialogGestion::setText(QString txt) {
    ui->label->setText(txt);
}

void DialogGestion::slot_update_database() {
    data_manager->empty_db();
    data_manager->parseActions();
    data_manager->parseItemproperties();
    data_manager->parseEquipementItemType();
    data_manager->parseStates();
    ui->pb_update_files->setEnabled(false);
    ui->pb_update_data_base->setEnabled(false);
    ui->pb_update_images->setEnabled(false);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);

    parser = new ParseItemThread();
    parser->setDatamanager(data_manager);
    connect(data_manager,&c_datamanager::newItem,this,&DialogGestion::slot_new_item);
    connect(data_manager,&c_datamanager::updateItemFinished,this,&DialogGestion::slot_endUpdateItems);
    parser->start();
}

void DialogGestion::slot_new_item(QString /**/, int index, int size) {
    ui->progressBar->setMaximum(size);
    ui->progressBar->setValue(index+1);
}

void DialogGestion::slot_endUpdateItems() {
    disconnect(data_manager,&c_datamanager::newItem,this,&DialogGestion::slot_new_item);
    disconnect(data_manager,&c_datamanager::updateItemFinished,this,&DialogGestion::slot_endUpdateItems);
    ui->progressBar->setValue(ui->progressBar->maximum());
    ui->pb_update_files->setEnabled(true);
    ui->pb_update_data_base->setEnabled(true);
    ui->pb_update_images->setEnabled(true);
}

void DialogGestion::slot_update_images() {
    connect(data_manager,&c_datamanager::newImage,this,&DialogGestion::slot_new_image);
    connect(data_manager,&c_datamanager::downloadImageFinished,this,&DialogGestion::slot_endUpdateImages);
    ui->progressBar->setValue(0);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    ui->pb_update_files->setEnabled(false);
    ui->pb_update_data_base->setEnabled(false);
    ui->pb_update_images->setEnabled(false);
    data_manager->getImages();
}

void DialogGestion::slot_new_image(int index, int size) {
    ui->progressBar->setMaximum(size);
    ui->progressBar->setValue(index+1);
}

void DialogGestion::slot_endUpdateImages() {
    disconnect(data_manager,&c_datamanager::newImage,this,&DialogGestion::slot_new_image);
    disconnect(data_manager,&c_datamanager::downloadImageFinished,this,&DialogGestion::slot_endUpdateImages);
    ui->progressBar->setValue(ui->progressBar->maximum());
    ui->pb_update_files->setEnabled(true);
    ui->pb_update_data_base->setEnabled(true);
    ui->pb_update_images->setEnabled(true);
}

void DialogGestion::set_version(QString _version) {
    version = _version;
}

void DialogGestion::slot_on_close() {
    data_manager->slot_stop();
    close();
}
