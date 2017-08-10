#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>

class DatabaseManager {
public:
    static DatabaseManager* getInstance();
    void init();

private:
    DatabaseManager();
    DatabaseManager(const DatabaseManager& obj) = delete;
    DatabaseManager(const DatabaseManager&& obj) = delete;
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
