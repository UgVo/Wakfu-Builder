#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include <QProgressBar>
#include <QThread>
#include <QColor>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QStackedLayout>
#include <QMovie>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QEventLoop>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDatabase>
#include <QPropertyAnimation>
#include "utilities/c_dbmanager.h"
#include "utilities/c_effect.h"
#include "utilities/c_networkmanager.h"
#include "utilities/c_datamanager.h"
#include "ui/c_dialoggestion.h"
#include "utilities/c_tokenizer.h"
#include "utilities/c_item_model.h"
#include "ui/c_builder_view.h"
#include "ui/c_entry_point.h"
#include "ui/c_bdd_password_dialog.h"

#include "utilities/c_io_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class InitModelThread : public QThread
{
    Q_OBJECT
    void run() override {
        model->init();
        emit resultReady();
    }
    c_item_model *model;
signals:
    void resultReady();

public:
    void setModel(c_item_model *_model) {
        model = _model;
    }
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getApp_path() const;

private:
    Ui::MainWindow *ui;
    QString app_path;
    c_dbmanager *database_manager;
    c_datamanager datamanager;
    DialogGestion *diag;
    QList<c_builder_view*> builder_list;
    c_entry_point* entry_point;
    QLabel *connection_status;

public slots:
    void slot_check_version_clicked();
    void slot_version_check(QString version);

    void test();
    void test_interpret_effect();

    void slot_actionCr_er_nouveau_Build_clicked();
    void slot_on_close_table(const int &index);
    void slot_actionSauvegarder_Build();
    void slot_action_open_Depuis_un_fichier();
    void slot_action_save_Vers_la_base_de_donnee();
    void slot_action_open_Depuis_la_base_de_donn_e();
    void slot_actionEnregistrer();
    void slot_action_connection_bdd();

    void slot_creation_builder();
    void slot_creation_finished();

    void set_save_enabled(bool flag);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    void slot_connection_status(bool status);
    virtual void resizeEvent(QResizeEvent *event);


signals:
    void init_done();
    void shift_pressed(bool state);
};


#endif // MAINWINDOW_H
