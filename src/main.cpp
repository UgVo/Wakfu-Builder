#include "mainwindow.h"
#include "utilities/c_effect.h"
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QSplashScreen>

static QString file_path = "";

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QFile data(file_path);
    data.open(QFile::WriteOnly | QFile::Append);
    QTextStream out(&data);
    QByteArray localMsg = msg.toLocal8Bit();
    QString msg_f;
       switch (type) {
       case QtDebugMsg:
           msg_f = QString("[%1] Debug: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
           qDebug() << msg_f;
           out << msg_f;
           break;
       case QtInfoMsg:
           msg_f = QString("[%1] Info: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
           qDebug() << msg_f;
           out << msg_f;
           break;
       case QtWarningMsg:
           msg_f = QString("[%1] Warning: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
           qDebug() << msg_f;
           out << msg_f;
           break;
       case QtCriticalMsg:
           msg_f =  QString("[%1] Critical: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
           qDebug() << msg_f;
           out << msg_f;
           break;
       case QtFatalMsg:
           msg_f = QString("[%1] Fatal: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
           qDebug() << msg_f;
           out << msg_f;
           abort();
       }
}

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        file_path = QString(qApp->applicationDirPath() + "/log/log%1.txt").arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss"));
        qInstallMessageHandler(myMessageOutput);
        QPixmap pixmap(":/images/divers/splash.png");
        QSplashScreen splash(pixmap);
        splash.setMaximumSize(QSize(500,500));
        splash.show();
        a.processEvents();
        MainWindow w;
        splash.showMessage("Loading items 1/2",Qt::AlignLeft,Qt::white);
        w.load_item_model();
        splash.showMessage("Loading items 2/2",Qt::AlignLeft,Qt::white);
        w.load_completer();
        w.show();
        splash.finish(&w);
        return a.exec();
    } catch (const std::exception & e) {
        qFatal(e.what());
    }
}
