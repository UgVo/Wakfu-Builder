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

    diag = new DialogGestion(&datamanager,datamanager.getVersion(),this);

    QObject::connect(ui->actionCheck_new_version,SIGNAL(triggered()),this,SLOT(slot_check_version_clicked()),Qt::UniqueConnection);
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
