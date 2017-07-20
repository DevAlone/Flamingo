#include "user.h"

#include <QDebug>

#include <db/databasemanager.h>

#include "exceptions/include.h"

#include <exceptions/modelerror.h>

int UserPrivate::activeUserId = -1;
std::shared_ptr<User> UserPrivate::activeUser;

User::User()
{
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString& name)
{
    if (name.size() > 255)
        throw std::logic_error(
            "size of user name cannot be bigger than 255 symbols");
    this->name = name;
}

QSqlError User::createTable()
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

std::vector<std::shared_ptr<User>> User::getAll()
{
    std::vector<std::shared_ptr<User>> result;

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

        auto userModel = std::make_shared<User>();
        userModel->id = id;
        userModel->name = name;
        result.push_back(userModel);
    }

    return result;
}

void User::setActiveUserId(int userId)
{
    UserPrivate::activeUserId = userId;
}

int User::getActiveUserId()
{
    return UserPrivate::activeUserId;
}

std::shared_ptr<User> User::getActiveUser()
{
    // TODO: optimize this shit;
    std::vector<std::shared_ptr<User>> users = User::getAll();

    UserPrivate::activeUser.reset();
    int index = UserPrivate::activeUserId;
    for (auto& user : users) {
        if (user->getId() == User::getActiveUserId()) {
            UserPrivate::activeUser = user;
            break;
        }
    }

    if (UserPrivate::activeUser)
        return UserPrivate::activeUser;
    else
        throw ModelError(
            QObject::tr("User not found"));
}

void User::save()
{
    Model::save();

    for (auto& course : courses) {
        course.setUserId(id);
        course.save();
    }
}

void User::sqlInsert()
{
    // user doesn't exist
    QSqlQuery insertQuery;
    insertQuery.prepare(R"(
                        INSERT INTO  main.users (name)
                        VALUES (:name);
                        )");
    insertQuery.bindValue(":name", name);
    if (!insertQuery.exec())
        throw ModelSavingError(
            "Unable to insert User",
            insertQuery.lastError());

    setLastInsertedId(insertQuery);
}

void User::sqlUpdate()
{
    // user probably exists
    QSqlQuery updateQuery;
    updateQuery.prepare(R"(
                        UPDATE main.users
                        SET name = :name
                        WHERE id=:id;
                        )");
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":id", id);

    if (!updateQuery.exec())
        throw ModelSavingError(
            "Unable to update User",
            updateQuery.lastError());
}

std::vector<Course>& User::getCourses()
{
    if (id >= 0) {
        // TODO: update from db
    }
    return courses;
}

User::operator QString() const
{
    return name;
}
