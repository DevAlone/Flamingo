#include "course.h"

#include <QtCore>
#include <QtSql>

#include <exceptions/modelsavingerror.h>

Course::Course(QString name)
    : name(name)
{
}

QString Course::getName() const
{
    return name;
}

void Course::setName(const QString& value)
{
    name = value;
}

void Course::addModule(Module& module)
{
    modules.push_back(module);
}

void Course::addModules(std::vector<Module>& modules)
{
    for (auto& module : modules)
        addModule(module);
}

QString Course::getAuthor() const
{
    return author;
}

void Course::setAuthor(const QString& value)
{
    author = value;
}

unsigned char Course::getLevel() const
{
    return level;
}

void Course::setLevel(unsigned char value)
{
    level = value;
}

std::vector<Module>& Course::getModules()
{
    return modules;
}

void Course::save()
{
    Model::save();

    for (auto& module : modules) {
        module.setCourseId(id);
        module.save();
    }
}

void Course::sqlInsert()
{
    if (userId < 0)
        // TODO: maybe remove this
        throw ModelSavingError("Unable to save Course. userId must be >= 0");

    QSqlQuery insertQuery;
    // TODO: d
    insertQuery.prepare(R"(
                        INSERT INTO main.courses (name, author, level, userId)
                        VALUES (:name, :author, :level, :userId);
                        )");
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":author", author);
    insertQuery.bindValue(":level", int(level));
    insertQuery.bindValue(":userId", userId);

    if (!insertQuery.exec())
        throw ModelSavingError(
            "Unable to save Course",
            insertQuery.lastError());

    setLastInsertedId(insertQuery);
}

void Course::sqlUpdate()
{
    // update
    QSqlQuery updateQuery;
    updateQuery.prepare(R"(
                        UPDATE main.courses
                        SET name = :name, author = :author, level = :level
                        WHERE id=:id;
                        )");
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":author", author);
    updateQuery.bindValue(":level", level);
    updateQuery.bindValue(":id", id);

    if (!updateQuery.exec())
        throw ModelSavingError(
            "Unable to update Course",
            updateQuery.lastError());
}

QSqlError Course::createTable()
{
    QSqlQuery query(R"(
                    CREATE TABLE IF NOT EXISTS main.courses (
                                        id integer PRIMARY KEY,
                                        name text NOT NULL,
                                        author text NOT NULL,
                                        level integer NOT NULL,
                                        userId integer,
                                        FOREIGN KEY(userId) REFERENCES users(id)
                                        ON UPDATE CASCADE
                                        ON DELETE CASCADE);
                    )");
    QSqlError error;
    if (!query.exec())
        error = query.lastError();

    return error;
}

int Course::getUserId() const
{
    return userId;
}

void Course::setUserId(int value)
{
    userId = value;
}
