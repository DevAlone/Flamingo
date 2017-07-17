#include "databasemanager.h"

#include <QSqlDatabase>

#include <models/usermodel.h>

#include <QDebug>

DatabaseManager* DatabaseManager::getInstance()
{
    static DatabaseManager* obj = nullptr;
    if (obj == nullptr) {
        obj = new DatabaseManager();

        obj->init();
    }

    return obj;
}

DatabaseManager::DatabaseManager()
{
}

void DatabaseManager::init()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        // TODO: handle it
        throw std::exception();
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("main.db");
    if (!db.open()) {
        // TODO: hangle this shit
        throw std::exception();
    }

    // TODO: create tables
    QSqlError error = UserModel::createTable();
    if (error.type() != QSqlError::NoError) {
        // TODO: handle it

        //        QString error = db.lastError().text();
        qDebug() << error.text();

        throw std::exception();
    }
}

QSqlDatabase DatabaseManager::getDb() const
{
    return db;
}
