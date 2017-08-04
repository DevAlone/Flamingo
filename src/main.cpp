#include "parser/include.h"

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

// It's just for debug. Remove it later
void tick()
{
    QFile styleFile("style.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString style = styleFile.readAll();

        qApp->setStyleSheet(style);
    }
    QTimer::singleShot(100, tick);
}

void initSettings();
void initCss();

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/images/flamingo1.png");
    FlamingoSplashScreen splash(pixmap);

    splash.show();

    splash.showMessage(QObject::tr("Initializing settings and styles..."));

    initSettings();
    initCss();
    // TODO: remove it later
    QTimer::singleShot(3000, tick);

    splash.showMessage(QObject::tr("Initializing database..."));

    DatabaseManager* dbManager = DatabaseManager::getInstance();

    dbManager->init();

    MainWindow w;

    w.show();

    splash.finish(&w);

    return a.exec();
}

void initSettings()
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("DevAlone");
    QApplication::setApplicationName("Flamingo");
    QSettings s;
    s.setValue("courseParser/courseDirectory", "courses");
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
