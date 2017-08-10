#include "course.h"

#include <QtCore>
#include <QtSql>

#include <exceptions/modelerror.h>
#include <exceptions/modelsavingerror.h>

Course::Course(QString name)
    : name(name)
{
}

Course::operator QString() const
{
    return name;
}

QString Course::getName() const
{
    return name;
}

void Course::setName(const QString& value)
{
    name = value;
}

void Course::addModule(std::shared_ptr<Module> module)
{
    modules.push_back(module);
}

void Course::addModules(std::vector<std::shared_ptr<Module>>& modules)
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

void Course::setLevel(int value)
{
    if (value < 1 || value > 10)
        throw ModelError(
            QObject::tr("Logic error: level must be from 1 to 10(included)"));
    level = value;
}

std::vector<std::shared_ptr<Module>>& Course::getModules()
{
    if (id >= 0) {
        modules = Module::getByCourseId(id);
    }
    return modules;
}

void Course::save()
{
    Model::save();

    for (auto& module : modules) {
        module->setCourseId(id);
        module->save();
    }
}

bool Course::update()
{
    if (id < 0)
        return false;

    bool isChanged = false;

    QSqlQuery selectQuery;
    selectQuery.prepare(R"(
                        SELECT name, author, level, description, languageCode FROM main.courses
                        WHERE id = :id;
                        )");
    selectQuery.bindValue(":id", id);

    if (!selectQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to get Course from database"),
            selectQuery.lastError());
    }

    while (selectQuery.next()) {
        bool isOk;
        QString name = selectQuery.value(0).toString();
        QString author = selectQuery.value(1).toString();
        int level = selectQuery.value(2).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get Course level from database"));
        QString description = selectQuery.value(3).toString();
        QString languageCode = selectQuery.value(4).toString();

        if (getName() != name) {
            isChanged = true;
            setName(name);
        }
        if (getAuthor() != author) {
            isChanged = true;
            setAuthor(author);
        }
        if (getLevel() != level) {
            isChanged = true;
            setLevel(level);
        }
        if (getDescription() != description) {
            isChanged = true;
            setDescription(description);
        }
        if (getLanguageCode() != languageCode) {
            isChanged = true;
            setLanguageCode(languageCode);
        }
    }

    return isChanged;
}

bool Course::remove()
{
    if (id < 0)
        return false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare(R"(
                        DELETE FROM main.courses
                        WHERE id = :id;
                        )");
    deleteQuery.bindValue(":id", id);

    if (!deleteQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to remove Course from database"),
            deleteQuery.lastError());
    }

    for (auto& module : getModules())
        module->remove();

    id = -1;

    return true;
}

void Course::sqlInsert()
{
    if (userId < 0)
        // TODO: maybe remove this
        throw ModelSavingError("Unable to save Course. userId must be >= 0");

    QSqlQuery insertQuery;
    // TODO: d
    insertQuery.prepare(R"(
                        INSERT INTO main.courses (name, author, level, userId, description, languageCode)
                        VALUES (:name, :author, :level, :userId, :description, :languageCode);
                        )");
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":author", author);
    insertQuery.bindValue(":level", int(level));
    insertQuery.bindValue(":userId", userId);
    insertQuery.bindValue(":description", description);
    insertQuery.bindValue(":languageCode", languageCode);

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
                        SET name = :name, author = :author, level = :level, description = :description, languageCode = :languageCode
                        WHERE id=:id;
                        )");
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":author", author);
    updateQuery.bindValue(":level", level);
    updateQuery.bindValue(":id", id);
    updateQuery.bindValue(":description", description);
    updateQuery.bindValue(":languageCode", languageCode);

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
                    description text NOT NULL,
                    languageCode text NOT NULL,
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

std::vector<std::shared_ptr<Course>> Course::getAll()
{
    return filter(-1);
}

std::vector<std::shared_ptr<Course>> Course::getByUserId(int userId)
{
    return filter(userId);
}

std::vector<std::shared_ptr<Course>> Course::filter(int userId)
{
    std::vector<std::shared_ptr<Course>> result;

    QString query = R"(
                    SELECT id, name, author, level, description, languageCode, userId
                    FROM main.courses
                    )";
    if (userId >= 0) {
        query += "WHERE userId = :userId";
    }

    query += ";";

    QSqlQuery selectQuery;
    selectQuery.prepare(query);

    if (userId >= 0)
        selectQuery.bindValue(":userId", userId);

    if (!selectQuery.exec()) {
        throw ModelSqlError(
            "Unable to fetch courses from DB",
            selectQuery.lastError());
    }

    while (selectQuery.next()) {
        bool isOk;
        int id = selectQuery.value(0).toInt(&isOk);
        if (!isOk) {
            throw ModelError(
                QObject::tr("Unable to get id from course"));
        }
        QString name = selectQuery.value(1).toString();

        QString author = selectQuery.value(2).toString();
        int level = selectQuery.value(3).toInt(&isOk);
        if (!isOk) {
            throw ModelError(
                QObject::tr("Unable to get level from course"));
        }
        QString description = selectQuery.value(4).toString();
        QString languageCode = selectQuery.value(5).toString();
        int userId = selectQuery.value(6).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get userId from course"));

        auto courseModel = std::make_shared<Course>(name);
        courseModel->id = id;
        courseModel->author = author;
        courseModel->level = level;
        courseModel->description = description;
        courseModel->languageCode = languageCode;
        courseModel->userId = userId;
        result.push_back(courseModel);
    }
    return result;
}

QString Course::getLanguageCode() const
{
    return languageCode;
}

void Course::setLanguageCode(const QString& value)
{
    languageCode = value;
}

QString Course::getDescription() const
{
    return description;
}

void Course::setDescription(const QString& value)
{
    description = value;
}

int Course::getUserId() const
{
    return userId;
}

void Course::setUserId(int value)
{
    userId = value;
}
