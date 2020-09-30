#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <QObject>
#include <QtDebug>
#include <iostream>
#include <QLoggingCategory>
#include <qfile.h>
#include <QMutex>



namespace Toolkit
{
/*Пути и мьютексы*/
QString debugPath;
QString  infoPath;
QString warningPath;
QString criticalPath;
QString fatalPath;

QMutex debugMutex;
QMutex infoMutex;
QMutex warningMutex;
QMutex criticalMutex;
QMutex fatalMutex;

bool isSet = false;
const QtMessageHandler DEFAULTHANDLER = qInstallMessageHandler(0);
/* Функция установки путей сохранения. Если не выполнена - сообщения будут отправлятся дефолтному хендлеру */
void setPath(const QString &debug,const QString &info,const QString &warning, const QString& critical,const QString& fatal )
{
    debugPath = debug;
    infoPath = info;
    warningPath = warning;
    criticalPath = critical;
    fatalPath = fatal;
    isSet = true;

}

/* Методы записи */
void writeDebug(const QString &msg)
{
    QMutexLocker m(&debugMutex);
    QFile file(debugPath);
    if (file.open(QIODevice::Append)) {
        file.write(msg.toStdString().c_str());
        file.write("\n");
    }
    file.close();
}

void writeInfo(const QString &msg)
{
    QMutexLocker m(&infoMutex);
    QFile file(infoPath);
    if (file.open(QIODevice::Append)) {
        file.write(msg.toStdString().c_str());
        file.write("\n");
    }
    file.close();
}

void writeCritical(const QString &msg)
{
    QMutexLocker m(&criticalMutex);
    QFile file(criticalPath);
    if (file.open(QIODevice::Append)) {
        file.write(msg.toStdString().c_str());
        file.write("\n");
    }
    file.close();
}

void writeWarning(const QString &msg)
{
    QMutexLocker m(&warningMutex);
    QFile file(warningPath);
    if (file.open(QIODevice::Append)) {
        file.write(msg.toStdString().c_str());
        file.write("\n");
    }
    file.close();
}

void writeFatal(const QString &msg)
{
    QMutexLocker m(&fatalMutex);
    QFile file(fatalPath);
    if (file.open(QIODevice::Append)) {
        file.write(msg.toStdString().c_str());
        file.write("\n");
    }
    file.close();
}

/* Непосредственно обработчик */
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(isSet)
    {
        switch (type) {
        case QtDebugMsg:
            writeDebug(msg);
            break;
        case QtInfoMsg:
            writeInfo(msg);
            break;
        case QtWarningMsg:
            writeWarning(msg);
            break;
        case QtCriticalMsg:
            writeCritical(msg);
            break;
        case QtFatalMsg:
            writeFatal(msg);
            break;
        }
    }
    else
    {
        DEFAULTHANDLER(type, context, msg);
    }


};

}


#endif // PEREHVAT_H
