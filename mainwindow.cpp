#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSslSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QFontDatabase::addApplicationFont(":/wci.ttf");
    app_path = qApp->applicationDirPath();
    ui->setupUi(this);
    database_manager = new c_dbmanager(&datamanager);
    datamanager.setDBManager(database_manager);
    ui->actionCheck_new_version->setIcon(QIcon(":/images/divers/update32.png"));
    set_save_enabled(false);
    ui->tabWidget->setTabsClosable(true);
    this->setStyleSheet(QString("MainWindow {background-color : %1}").arg(app_color::dark_blue));

    QCoreApplication::setApplicationName(QString("Builder Wakfu"));
    setWindowTitle(QCoreApplication::applicationName());

    diag = new DialogGestion(&datamanager,datamanager.getVersion(),this);

    QObject::connect(ui->actionCheck_new_version,SIGNAL(triggered()),this,SLOT(slot_check_version_clicked()),Qt::UniqueConnection);
    QObject::connect(ui->actionCr_er_nouveau_Build,&QAction::triggered,this,&MainWindow::slot_actionCr_er_nouveau_Build_clicked);
    QObject::connect(ui->tabWidget,&QTabWidget::tabCloseRequested,this,&MainWindow::slot_on_close_table);
    QObject::connect(ui->actionSauvegarder_Build,&QAction::triggered,this,&MainWindow::slot_actionSauvegarder_Build);
    QObject::connect(ui->action_open_Depuis_un_fichier,&QAction::triggered,this,&MainWindow::slot_action_open_Depuis_un_fichier);
    QObject::connect(ui->action_save_Vers_la_base_de_donnee,&QAction::triggered,this,&MainWindow::slot_action_save_Vers_la_base_de_donnee);
    QObject::connect(ui->action_open_Depuis_la_base_de_donn_e,&QAction::triggered,this,&MainWindow::slot_action_open_Depuis_la_base_de_donn_e);
    QObject::connect(ui->actionEnregistrer,&QAction::triggered,this,&MainWindow::slot_actionEnregistrer);
    QObject::connect(database_manager,&c_dbmanager::signal_connection_status,this,&MainWindow::slot_connection_status);
    QObject::connect(ui->actionConnexion_bdd,&QAction::triggered,this,&MainWindow::slot_action_connection_bdd);

    entry_point = new c_entry_point(database_manager,this);
    ui->page_1->layout()->addWidget(entry_point);

    QObject::connect(entry_point,&c_entry_point::new_clicked,this,&MainWindow::slot_actionCr_er_nouveau_Build_clicked);
    QObject::connect(entry_point,&c_entry_point::first_animation_finished,this,&MainWindow::slot_creation_builder);
    QObject::connect(entry_point,&c_entry_point::second_animation_finished,this,&MainWindow::slot_creation_finished);
    QObject::connect(entry_point,&c_entry_point::load_builder_from,this,&MainWindow::slot_open_builder);
    //QObject::connect(entry_point,&QPushButton::clicked,this,&MainWindow::slot_open_button);

    this->setWindowState(Qt::WindowMaximized);

    ui->label_licence_1->setStyleSheet("color:white");
    ui->label_licence_2->setStyleSheet("color:white");



    connection_status = new QLabel(this);
    connection_status->setMinimumSize(QSize(40,40));
    connection_status->setMaximumSize(QSize(40,40));
    connection_status->setPixmap(QPixmap(":/images/divers/Network-Connected-icon.png"));
    connection_status->setBackgroundRole(QPalette::Base);
    connection_status->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    connection_status->setScaledContents(true);
    connection_status->show();
    ui->actionConnexion_bdd->setIcon(QIcon(":/images/divers/Network-Connected-icon.png"));

    database_manager->connect();
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::getApp_path() const
{
    return app_path;
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

void MainWindow::slot_actionCr_er_nouveau_Build_clicked() {
    set_save_enabled(true);
    builder_list.push_back(new c_builder_view(database_manager,this));
    ui->tabWidget->addTab(builder_list.last(),QString("Builder %1").arg(builder_list.size()));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::slot_check_version_clicked() {
    datamanager.checkVersion();
    QObject::connect(&datamanager,SIGNAL(newVersion(QString)),this,SLOT(slot_version_check(QString)));
}

void MainWindow::slot_version_check(QString version) {
    QObject::disconnect(&datamanager,SIGNAL(newVersion(QString)),this,SLOT(slot_version_check(QString)));
    QString local_version = datamanager.getVersion();
    diag->set_version(version);
    QString format = QString("<font color=\"%2\">%1</font>").arg(local_version,QColor::fromRgb(0,255,0).name());
    if (version != local_version) {
        diag->setText("New version available");
        format = QString("<font color=\"%3\">%1</font> => <font color=\"%4\">%2</font>").arg(local_version,version,QColor::fromRgb(255,0,0).name(),QColor::fromRgb(0,255,0).name());
    }
    diag->setVersionText(format);
    diag->show();
}

void MainWindow::slot_on_close_table(const int &index) {
    if (index == -1) {
        return;
    }

    QWidget* tabItem = ui->tabWidget->widget(index);
    // Check for save
    ui->tabWidget->removeTab(index);
    builder_list.removeAt(index);

    delete(tabItem);
    tabItem = nullptr;

    if (!builder_list.size()) {
        set_save_enabled(false);
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::slot_actionSauvegarder_Build() {
    if (ui->tabWidget->currentIndex() == -1) {
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Build"), app_path + "/save", tr("Json files (*.json)"));

    if (!fileName.isEmpty()) {
        c_builder_view* builder = static_cast<c_builder_view*>(ui->tabWidget->currentWidget());
        builder->slot_save(c_io_manager::jsonformat::file,fileName);
    }
}

void MainWindow::slot_action_open_Depuis_un_fichier() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Save Build"), app_path + "/save", tr("Json files (*.json)"));
    if (!fileName.isEmpty()) {
        c_builder_view *builder = new c_builder_view(database_manager,this);
        if (builder->slot_load(c_io_manager::jsonformat::file,fileName)) {
            set_save_enabled(true);
            builder_list.push_back(builder);
            ui->tabWidget->addTab(builder,QString("Builder %1").arg(builder_list.size()));
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
            ui->stackedWidget->setCurrentIndex(1);
        } else {
            builder->deleteLater();
        }
    }
}

void MainWindow::slot_action_save_Vers_la_base_de_donnee() {
    if (ui->tabWidget->currentIndex() == -1) {
        return;
    }
    c_builder_view* builder = static_cast<c_builder_view*>(ui->tabWidget->currentWidget());
    builder->slot_save(c_io_manager::jsonformat::database);
}

void MainWindow::slot_action_open_Depuis_la_base_de_donn_e() {
    c_builder_view *builder = new c_builder_view(database_manager,this);
    if (builder->slot_load(c_io_manager::jsonformat::database)) {
        set_save_enabled(true);
        builder_list.push_back(builder);
        ui->tabWidget->addTab(builder,QString("Builder %1").arg(builder_list.size()));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::slot_actionEnregistrer() {
    if (ui->tabWidget->currentIndex() == -1) {
        return;
    }
    c_builder_view* builder = static_cast<c_builder_view*>(ui->tabWidget->currentWidget());
    if (!builder->getId()) {
        QMessageBox::critical(this,"Pas de sauvegarde préalable","Le build n'a pas eu de sauvegarde préalable, utilisez \"Enregistrer vers la base de donnée \" ou \"Enregistrer vers un fichier\" plutôt.");
    } else if (builder->getId() > 0) {
        builder->slot_update(c_io_manager::jsonformat::database);
    } else if (builder->getId() == -1) {
        builder->slot_update(c_io_manager::jsonformat::file);
    }
}

void MainWindow::slot_action_connection_bdd() {
    c_bdd_password_dialog dial;
    QString password;
    if (dial.exec() == QDialog::Accepted) {
        password = dial.get_password();
    }
    database_manager->connect(password);
    datamanager.savePassword(password);
}

void MainWindow::slot_creation_builder() {
    QObject::disconnect(entry_point,&c_entry_point::first_animation_finished,this,&MainWindow::slot_creation_builder);set_save_enabled(true);
    builder_list.push_back(new c_builder_view(database_manager,this));
    ui->tabWidget->addTab(builder_list.last(),QString("Builder %1").arg(builder_list.size()));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    QThread::msleep(10);
    builder_list.last()->update();
    entry_point->slot_creation_builder_anim();
}

void MainWindow::slot_open_builder(const c_io_manager::jsonformat format, QString path_json, int id) {
    QObject::disconnect(entry_point,&c_entry_point::load_builder_from,this,&MainWindow::slot_open_builder);
    builder_list.push_back(new c_builder_view(database_manager,this));
    builder_list.last()->slot_loadFrom(format,path_json,id);
    ui->tabWidget->addTab(builder_list.last(),QString("Builder %1").arg(builder_list.size()));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    QThread::msleep(10);
    builder_list.last()->update();
    entry_point->slot_creation_builder_anim();
    set_save_enabled(true);
}

void MainWindow::slot_creation_finished() {
    QObject::disconnect(entry_point,&c_entry_point::second_animation_finished,this,&MainWindow::slot_creation_finished);
    entry_point->deleteLater();
    entry_point = new c_entry_point(database_manager,this);
    ui->page_1->layout()->addWidget(entry_point);
    QObject::connect(entry_point,&c_entry_point::new_clicked,this,&MainWindow::slot_actionCr_er_nouveau_Build_clicked);
    QObject::connect(entry_point,&c_entry_point::first_animation_finished,this,&MainWindow::slot_creation_builder);
    QObject::connect(entry_point,&c_entry_point::second_animation_finished,this,&MainWindow::slot_creation_finished);
    QObject::connect(entry_point,&c_entry_point::load_builder_from,this,&MainWindow::slot_open_builder);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::set_save_enabled(bool flag) {
    ui->actionSauvegarder_Build->setEnabled(flag);
    ui->action_save_Vers_la_base_de_donnee->setEnabled(flag);
    ui->actionEnregistrer->setEnabled(flag);
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "keyPressEvent" <<  event->key();
    if (event->key() == Qt::Key_Shift) {
        emit shift_pressed(true);
    } else if (event->matches(QKeySequence::Save)) {
        slot_actionEnregistrer();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    qDebug() << "keyReleaseEvent" << event->key();
    if (event->key() == Qt::Key_Shift) {
        emit shift_pressed(false);
    }
}

void MainWindow::slot_connection_status(bool status) {
    qDebug() << status;
    connection_status->setPixmap(QPixmap(QString(":/images/divers/Network-%1onnected-icon.png").arg(status?"C":"Disc")));
    connection_status->setBackgroundRole(QPalette::Base);
    connection_status->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    connection_status->setScaledContents(true);
    ui->actionConnexion_bdd->setIcon(QIcon(QString(":/images/divers/Network-%1onnected-icon.png").arg(status?"C":"Disc")));
    ui->actionConnexion_bdd->setText(QString("%1onnexion Base de données").arg(status?"Dec":"C"));
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    connection_status->move(20,rect().height()-60);
    connection_status->show();
    connection_status->raise();
}
