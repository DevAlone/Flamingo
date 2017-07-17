#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>

class DatabaseManager {
public:
    static DatabaseManager* getInstance();

    QSqlDatabase getDb() const;

private:
    DatabaseManager();
    void init();
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
