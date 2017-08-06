#include "parser/include.h"

#include "flamingoapplication.h"
#include "flamingosplashscreen.h"
#include "mainwindow.h"

#include <QApplication>

#include <QSettings>

#include <QSplashScreen>
#include <QSqlDatabase>
#include <memory>
#include <thread>

#include <db/databasemanager.h>

#include <QDebug>
#include <QtCore>

#include <views/lesson/content_view/mediaplayerwidget.h>

// It's just for debug. Remove it later
void tick()
{
    QFile styleFile("style.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString style = styleFile.readAll();

        qApp->setStyleSheet(style);
    }
    QTimer::singleShot(3000, tick);
}

void initSettings();
void initCss();

int main(int argc, char* argv[])
{
    FlamingoApplication a(argc, argv);

    MediaPlayerWidget player;

    //    player.setSource(
    //        "/mnt/data/music/Music/Цой&Кино/05 - Кукушка.mp3");

    player.setSource(
        "/mnt/usbdata/movies/mythbusters/Season 01 (2003)/02 Cell Phone Destruction, Silicone Breasts, CD-ROM Shattering.avi");
    player.show();

    //    QPixmap pixmap(":/images/flamingo1.png");
    //    FlamingoSplashScreen splash(pixmap);

    //    splash.show();

    //    splash.showMessage(QObject::tr("Initializing settings and styles..."));

    //    initSettings();
    //    initCss();
    //    // TODO: remove it later
    //    QTimer::singleShot(3000, tick);

    //    splash.showMessage(QObject::tr("Initializing database..."));

    //    DatabaseManager* dbManager = DatabaseManager::getInstance();

    //    dbManager->init();

    //    MainWindow w;

    //    w.show();

    //    splash.finish(&w);

    return a.exec();
}

void initSettings()
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("DevAlone");
    QApplication::setApplicationName("Flamingo");
    QSettings s;

    if (s.value("courseParser/courseDirectory").isNull())
        s.setValue("courseParser/courseDirectory", "courses");
    if (s.value("interface/lesson/pageAutoSwitchTime").isNull())
        s.setValue("interface/lesson/pageAutoSwitchTime", 500);
}

void initCss()
{
    QString style = "";
    QFile resStyleFile(":/css/style.css");

    if (!resStyleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error during opening resource style file";
    } else {
        style += resStyleFile.readAll();
    }

    QFile styleFile("style.css");

    if (!styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error during opening style file";
    } else {
        style += styleFile.readAll();
    }

    qApp->setStyleSheet(style);
}
