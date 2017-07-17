#include "usermodel.h"

#include <QDebug>

#include <db/databasemanager.h>

UserModel::UserModel(QObject* parent)
    : QObject(parent)
{
}

QString UserModel::name() const
{
    return _name;
}

void UserModel::setName(const QString& name)
{
    if (name.size() > 255)
        throw std::logic_error(
            "size of user name cannot be bigger than 255 symbols");
    _name = name;
}

QSqlError UserModel::createTable()
{

    QSqlQuery query(R"(CREATE TABLE IF NOT EXISTS main.users (
                    id integer PRIMARY KEY,
                    name text NOT NULL
                    );)");

    QSqlError error;
    if (!query.exec())
        error = query.lastError();

    return error;
}

std::vector<std::shared_ptr<UserModel>> UserModel::getAll()
{
    std::vector<std::shared_ptr<UserModel>> result;

    QSqlQuery selectQuery("SELECT id, name FROM main.users");

    if (!selectQuery.exec()) {
        // TODO: handle error
    }

    while (selectQuery.next()) {
        bool isOk;
        int id = selectQuery.value(0).toInt(&isOk);
        if (!isOk) {
            // TODO: handle error
        }
        QString name = selectQuery.value(1).toString();

        auto userModel = std::make_shared<UserModel>();
        userModel->_id = id;
        userModel->_name = name;
        result.push_back(userModel);
    }

    return result;
}

void UserModel::setActiveUserId(int userId)
{
    activeUserId = userId;
}

int UserModel::getActiveUserId()
{
    return activeUserId;
}

bool UserModel::save()
{
    //    QSqlQuery selectQuery(R"(SELECT * FROM users)");

    if (_id < 0) {
        // user doesn't exist
        QSqlQuery insertQuery;
        insertQuery.prepare(R"(INSERT INTO  main.users (name)
                            VALUES (:name))");
        insertQuery.bindValue(":name", _name);
        if (!insertQuery.exec())
            return false;
        // TODO: get id from inserted item
        auto lastId = insertQuery.lastInsertId();
        if (!lastId.isValid()) {
            throw std::exception();
        }
        bool isOk;
        _id = lastId.toInt(&isOk);
        if (!isOk)
            throw std::exception();
        // TODO: handle it

    } else {
        // user probably exists
        QSqlQuery updateQuery;
        updateQuery.prepare(R"(UPDATE main.users
                            SET name = :name
                            WHERE id=:id)");
        updateQuery.bindValue(":name", _name);
        updateQuery.bindValue(":id", int(_id)); //TODO:do

        if (!updateQuery.exec())
            return false;
    }
}

int UserModel::id() const
{
    return _id;
}
