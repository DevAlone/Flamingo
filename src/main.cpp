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

using namespace parser;

#include <QDebug>
#include <QtCore>

// TODO: доделать сериализацию ответов

// TODO: It's just for debug. Remove it later
void tick()
{
    QFile styleFile("style.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString style = styleFile.readAll();

        qApp->setStyleSheet(style);
    }
    QTimer::singleShot(100, tick);
}

int main(int argc, char* argv[])
{
    qDebug() << QStyleFactory::keys().join(" ");

    QApplication a(argc, argv);

    QFile styleFile(":/css/style.css");

    if (!styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error during opening style file";
    } else {
        QString style = styleFile.readAll();
        a.setStyleSheet(style);
    }
    QTimer::singleShot(3000, tick);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("DevAlone");
    QApplication::setApplicationName("Flamingo");

    QSettings s;
    s.setValue("courseParser/courseDirectory", "courses");

    QPixmap pixmap(":/images/flamingo1.png");
    FlamingoSplashScreen splash(pixmap);

    splash.show();

    splash.showMessage(QObject::tr("Initializing database..."));

    DatabaseManager* dbManager = DatabaseManager::getInstance();

    MainWindow w;

    w.show();

    splash.finish(&w);

    return a.exec();
}
