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
#include "utilities/c_dbmanager.h"
#include "utilities/c_effect.h"
#include "utilities/c_networkmanager.h"
#include "utilities/c_datamanager.h"
#include "ui/c_dialoggestion.h"
#include "utilities/c_tokenizer.h"
#include "utilities/c_item_model.h"
#include "ui/c_builder_view.h"

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

private:
    Ui::MainWindow *ui;
    QString app_path;
    c_dbmanager database_manager;
    c_networkManager network_manager;
    c_datamanager datamanager;
    QProgressDialog *progressDial;
    ParseItemThread *parser;
    InitModelThread *initModel;
    DialogGestion *diag;
    c_item_display *it_display;
    c_item_model *item_model;
    QSortFilterProxyModel *model_proxy;
    QTableView *item_table_view;
    QLabel *item_table_bg;
    QStackedLayout *item_table_layout;
    QProgressBar *initModelProgress;
    QFuture<void> m_init;
    QFutureWatcher<void> m_watcher;
    QMovie *movie;
   c_builder_view* builder;

public slots:
    void slot_update_item(QWidget *parent);
    void slot_new_item(QString name, int index, int size);
    void slot_check_version_clicked();
    void slot_version_check(QString version);
    void slot_new_row(int index,int size);
    void slot_end_loading_model();
    static void init(MainWindow *);
    void slot_init_done();


    void test();
    void test_interpret_effect();

signals:
    void init_done();
};


#endif // MAINWINDOW_H
