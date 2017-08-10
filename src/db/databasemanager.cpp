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



#include <QSqlDatabase>

#include <models/include.h>

#include <QDebug>

#include <exceptions/createsqltableerror.h>
#include <exceptions/databaseinitializationerror.h>

DatabaseManager* DatabaseManager::getInstance()
{
    static DatabaseManager* obj = nullptr;
    if (obj == nullptr) {
        obj = new DatabaseManager;
    }

    return obj;
}

DatabaseManager::DatabaseManager()
{
}

void DatabaseManager::init()
{
    static bool isInitialized = false;
    if (isInitialized)
        throw DatabaseInitializationError(
            QObject::tr("Attempting to initialize database more than one time"));

    isInitialized = true;

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        throw DatabaseInitializationError(
            QObject::tr("There isn't sqlite driver :("));

    db = QSqlDatabase::addDatabase("QSQLITE");
    QDir programDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!programDir.exists())
        QDir().mkpath(programDir.absolutePath());

    QString dbFilePath(programDir.absoluteFilePath("main.db"));

    if (!QFileInfo(dbFilePath).exists()) {
        QFile dbFile(dbFilePath);
        dbFile.open(QIODevice::ReadWrite);
    }

    db.setDatabaseName(dbFilePath);

    if (!db.open())
        throw DatabaseInitializationError(
            QObject::tr("Database file \"main.db\" can't be opened: ") + dbFilePath);

    // TODO: create tables
    QSqlError error = User::createTable();
    if (error.type() != QSqlError::NoError)
        throw CreateSqlTableError(
            QObject::tr("Unable to create User table"),
            error);

    error = Course::createTable();
    if (error.type() != QSqlError::NoError)
        throw CreateSqlTableError(
            QObject::tr("Unable to create Course table"),
            error);

    error = Module::createTable();
    if (error.type() != QSqlError::NoError)
        throw CreateSqlTableError(
            QObject::tr("Unable to create Module table"),
            error);

    error = Submodule::createTable();
    if (error.type() != QSqlError::NoError)
        throw CreateSqlTableError(
            QObject::tr("Unable to create Submodule table"),
            error);

    error = Lesson::createTable();
    if (error.type() != QSqlError::NoError)
        throw CreateSqlTableError(
            QObject::tr("Unable to create Lesson table"),
            error);
}
