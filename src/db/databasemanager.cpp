#include "databasemanager.h"

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
    db.setDatabaseName("main.db");
    if (!db.open())
        throw DatabaseInitializationError(
            QObject::tr("Database file \"main.db\" can't be opened"));

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
