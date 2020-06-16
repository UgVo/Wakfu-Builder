#include "mainwindow.h"
#include "utilities/c_effect.h"
#include <QApplication>
#include <QFile>
#include <QDateTime>

static QString file_path = "";

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QFile data(file_path);
    data.open(QFile::WriteOnly | QFile::Append);
    QTextStream out(&data);
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        out << QString("[%1] Debug: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtInfoMsg:
        out << QString("[%1] Info: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtWarningMsg:
        out << QString("[%1] Warning: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtCriticalMsg:
        out << QString("[%1] Critical: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtFatalMsg:
        out << QString("[%1] Fatal: %2 (%3:%4, %5)\n").arg(QDateTime::currentDateTime().toString("hhmmss")).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    file_path = QString(qApp->applicationDirPath() + "/log/log%1.txt").arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss"));
    qInstallMessageHandler(myMessageOutput);
    MainWindow w;
    w.show();
    return a.exec();
}
