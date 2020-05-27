#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSslSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    app_path = qApp->applicationDirPath();
    ui->setupUi(this);
    datamanager.setDBManager(&database_manager);
    ui->actionCheck_new_version->setIcon(QIcon("images/divers/update32.png"));
    item_model = new c_item_model(&database_manager,this);
    model_proxy = new QSortFilterProxyModel;
    model_proxy->setSourceModel(item_model);

    item_table_layout = new QStackedLayout();
    initModelProgress = new QProgressBar();
    item_table_view = new QTableView();
    item_table_bg = new QLabel();
    movie = new QMovie("images/divers/loading.gif");
    item_table_bg->setMovie(movie);
    item_table_bg->setAlignment(Qt::AlignCenter);
    movie->start();

    item_table_view->setModel(model_proxy);
    item_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    item_table_view->setSortingEnabled(true);
    item_table_view->sortByColumn(0,Qt::AscendingOrder);

    QVBoxLayout *tab_3_layout =  new QVBoxLayout;
    item_table_layout->addWidget(item_table_view);
    item_table_layout->addWidget(item_table_bg);
    item_table_layout->setStackingMode(QStackedLayout::StackAll);

    ui->tab_3->setLayout(tab_3_layout);
    tab_3_layout->insertLayout(0,item_table_layout);
    tab_3_layout->addWidget(initModelProgress);

    diag = new DialogGestion(&datamanager,datamanager.getVersion(),this);

    build = new c_build;
    build_display =  new c_build_display(build);
    build_display->show();

    search = new c_search_widget(&database_manager);
    search->show();
    result_display = new c_result_display(&database_manager);
    result_display->show();
    status_build = new c_status_build;
    status_build->show();
    element_display = new c_elements_display;
    element_display->show();

    QObject::connect(search,&c_search_widget::new_search_result,result_display,&c_result_display::slot_new_search_result);
    QObject::connect(result_display,&c_result_display::item_doubleCliked,build_display,&c_build_display::equip_new_item);
    QObject::connect(status_build,&c_status_build::lvl_changed,search,&c_search_widget::setLvl);
    QObject::connect(status_build,&c_status_build::lvl_changed,build,&c_build::setLvl);
    QObject::connect(status_build,&c_status_build::bonus_changed,build,&c_build::slot_bonus_changed);
    QObject::connect(element_display,&c_elements_display::newElements,build,&c_build::setElements);

    QObject::connect(ui->actionCheck_new_version,SIGNAL(triggered()),this,SLOT(slot_check_version_clicked()),Qt::UniqueConnection);
    QObject::connect(item_model,SIGNAL(new_row(int,int)),this,SLOT(slot_new_row(int,int)));
    QObject::connect(&m_watcher,&QFutureWatcher<void>::finished,this,&MainWindow::slot_init_done);

    status_build->setLvl(200);
    //m_watcher.setFuture(m_init = QtConcurrent::run(init,this));

    test();
}

void MainWindow::init(MainWindow * MainWindow) {
    QElapsedTimer timer;
    timer.start();
    timer.restart();
    MainWindow->item_model->init();
}

void MainWindow::slot_init_done() {
    item_table_layout->removeWidget(item_table_bg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test() {
    c_tokenizer tok;
    qDebug() << "------------------- Debuging and tests -------------------";
    Q_ASSERT(!tok.formatString(QString("{[>2]?true:false}"),{1,2,0,5},10,2).compare("true"));
    Q_ASSERT(!tok.formatString(QString("{[>1]?true:false}"),{1,2,0,5},10,2).compare("true"));
    Q_ASSERT(!tok.formatString(QString("[#1] Point{[>2]?s:} de Vie"),{1,0},10,2).compare("1 Point de Vie"));
    Q_ASSERT(!tok.formatString(QString("[#1] Point{[>2]?s:} de Vie"),{1,1},10,2).compare("11 Points de Vie"));
    Q_ASSERT(!tok.formatString(QString("[#1] Point{[<2]?s:} de Vie"),{1,1},10,2).compare("11 Point de Vie"));
    Q_ASSERT(!tok.formatString(QString("[#1] Point{[=2]?s:} de Vie"),{1,1},10,2).compare("11 Point de Vie"));
    Q_ASSERT(!tok.formatString(QString("[#1] Point{[=2]?s:} de Vie"),{2,0},10,2).compare("2 Points de Vie"));
    Q_ASSERT(!tok.formatString(QString("[#1] Point{[~1]?s:} de Vie"),{1,1},10,2).compare("11 Points de Vie"));
    Q_ASSERT(!tok.formatString(QString("{[~3]?[#1] Résistance [#3]:[#1] Résistance sur [#2] élément{[>2]?s:} aléatoire{[>2]?s:}}"),{1,1,3,0},10,2).compare("11 Résistance sur 3 éléments aléatoires"));
    Q_ASSERT(!tok.formatString(QString("{[~3]?[#1] Résistance [#3]:[#1] Résistance sur [#2] élément{[>2]?s:} aléatoire{[>2]?s:}}"),{1,0,1,0},10,2).compare("1 Résistance sur 1 élément aléatoire"));
    Q_ASSERT(!tok.formatString(QString("{[~3]?[#1] Résistance [#3]:[#1] Résistance sur [#2] élément{[>2]?s:} aléatoire{[>2]?s:}}"),{1,0,1,0,0,0},10,2).compare("1 Résistance 0"));
    Q_ASSERT(!tok.formatString(QString("{[~3]?[#1] Maîtrise [#3]:[#1] Maîtrise sur [#2] élément{[>2]?s:} aléatoire{[>2]?s:}}"),{200,0,2,0},200,4).compare("200 Maîtrise sur 2 éléments aléatoires"));
    Q_ASSERT(!tok.formatString(QString("[ally] Applique [st5885] (1 par tour)"),{},200,4).compare("ally Applique [5885] (1 par tour)"));
    Q_ASSERT(tok.get_id_state("Applique [5885] (1 par tour)") == 5885);
    Q_ASSERT(tok.get_id_state("Applique (1 par tour)") == 0);

    this->setWindowState(Qt::WindowMinimized);
    result_display->slot_new_search_result({17543, 17544, 17545, 17546, 18005, 18381, 18464, 18537, 19062, 19432, 19746, 20278, 20757, 21207, 21707, 21868, 23924, 24309, 24329, 24331, 24725, 24790, 25073, 25076, 26288, 26498, 26500, 26502, 26506, 26508, 27026, 27030, 27038, 27354, 27358});
}

void MainWindow::test_interpret_effect() {
     c_tokenizer tok;
     qDebug() << tok.interpret_effect("12 PV");
     qDebug() << tok.interpret_effect("12 Points de Vie");
     qDebug() << tok.interpret_effect("12 Vol de Vie");
     qDebug() << tok.interpret_effect("1 Point de Vie");
     qDebug() << tok.interpret_effect("12 Résistance Feu");
     qDebug() << tok.interpret_effect("12 Résistance sur 2 élements");
     qDebug() << tok.interpret_effect("12 Maîtrise sur 5 éléments");
     qDebug() << tok.interpret_effect("-12  Maîtrise sur 5 éléments");
     qDebug() << tok.interpret_effect("12% Coup Critique");
     qDebug() << tok.interpret_effect("5 Niv. aux sorts Feu");
}

void MainWindow::slot_end_loading_model() {
    QObject::disconnect(item_model,SIGNAL(new_row(int,int)),this,SLOT(slot_new_row(int,int)));
    QObject::disconnect(initModel,SIGNAL(resultReady()),this,SLOT(slot_end_loading_model()));
    item_table_layout->removeWidget(item_table_bg);
    //item_table_view->setModel(model_proxy);
    item_table_view->resizeColumnsToContents();
    item_table_view->update();
}

void MainWindow::slot_new_row(int index,int size) {
    movie->jumpToNextFrame();
    initModelProgress->setMaximum(size);
    initModelProgress->setValue(index+1);
}

void MainWindow::slot_update_item(QWidget* parent) {
    parser = new ParseItemThread();
    parser->setDatamanager(&datamanager);
    //datamanager.moveToThread(&parser);
    QObject::connect(&datamanager,SIGNAL(newItem(QString,int,int)),this,SLOT(slot_new_item(QString,int,int)));
    progressDial = new QProgressDialog(parent);
    progressDial->show();
    parser->start();
    qDebug() << "parse item end";
}

void MainWindow::slot_new_item(QString name, int index, int size) {
    progressDial->setMaximum(size);
    progressDial->setLabelText(tr("Insert %1. (%2/%3)").arg(name).arg(index+1).arg(size));
    progressDial->setValue(index+1);
}

void MainWindow::slot_check_version_clicked() {
    datamanager.checkVersion();
    QObject::connect(&datamanager,SIGNAL(newVersion(QString)),this,SLOT(slot_version_check(QString)));
}

void MainWindow::slot_version_check(QString version) {
    QObject::disconnect(&datamanager,SIGNAL(newVersion(QString)),this,SLOT(slot_version_check(QString)));
    QString local_version = datamanager.getVersion();
    diag->set_version(version);
    QObject::connect(diag,SIGNAL(updateItem(QWidget*)),this,SLOT(slot_update_item(QWidget*)));
    QString format = QString("<font color=\"%2\">%1</font>").arg(local_version,QColor::fromRgb(0,255,0).name());
    if (version != local_version) {
        diag->setText("New version available");
        format = QString("<font color=\"%3\">%1</font> => <font color=\"%4\">%2</font>").arg(local_version,version,QColor::fromRgb(255,0,0).name(),QColor::fromRgb(0,255,0).name());
    }
    diag->setVersionText(format);
    diag->show();
}
