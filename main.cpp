#include "mainwindow.h"
#include <QTextCodec>
#include <QtGui>
#include <QApplication>
#include <QSettings>
#include <QDebug>

bool imitator;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QSettings* imSettings = new QSettings("kama-imitator", "imitator");
    if(!imSettings->contains("imitator")) {
        qDebug() << "Создаю концигурационный файл";
        imSettings->setValue("imitator", 1);
    }

    imitator = imSettings->value("imitator").toBool();
    delete imSettings;
    imitator ? qDebug() << "Запуск в режиме \"имитатор\"" : qDebug() << "Запуск в режиме \"основная работа\"";
    MainWindow w(0,
                 imitator ? createDummyUploader() : createRealUploader(),
                 imitator ? createImitationFrameHandler() : createRealFrameHandler());
//                 imitator ? createDummyNetworkDevice() : createRealNetworkDevice()
    w.show();
    return a.exec();
}
