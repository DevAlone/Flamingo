// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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

#include <iostream>

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
    try {
        FlamingoApplication a(argc, argv);

        QPixmap pixmap(":/images/flamingo1.png");
        FlamingoSplashScreen splash(pixmap);

        splash.show();

        splash.showMessage(QObject::tr("Initializing settings and styles..."));

        initSettings();
        initCss();
        // TODO: remove it later
        //    QTimer::singleShot(3000, tick);

        splash.showMessage(QObject::tr("Initializing database..."));

        DatabaseManager* dbManager = DatabaseManager::getInstance();

        dbManager->init();

        MainWindow w;

        w.show();

        splash.finish(&w);

        return a.exec();
    } catch (const Exception& ex) {
        std::cerr << "Exception: " << ex.getMessage().toStdString() << std::endl;
    }
    return -1;
}

void initSettings()
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("DevAlone");
    QApplication::setApplicationName("Flamingo");
    QSettings s;

    if (s.value("courseParser/courseDirectory").isNull()) {
        QDir homeDir(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        QDir coursesDir(homeDir.absoluteFilePath("flamingo_courses"));
        if (!coursesDir.exists())
            QDir().mkpath(coursesDir.absolutePath());

        s.setValue("courseParser/courseDirectory", coursesDir.absolutePath());
    }

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
