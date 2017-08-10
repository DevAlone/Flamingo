#include "submodule.h"

#include <QSqlQuery>

Submodule::Submodule(const QString& name)
    : ModuleItem(name)
{
    type = MODULE_ITEM_TYPE::SUBMODULE;
}

Submodule::Submodule(const Submodule& other)
    : ModuleItem(other.name)
{
    lessons.clear();
    for (auto& lesson : lessons) {
        lessons.push_back(std::make_shared<Lesson>(*lesson));
    }
}

Submodule& Submodule::operator=(const Submodule& other)

{
    name = other.name;
    lessons.clear();
    for (auto& lesson : lessons) {
        lessons.push_back(std::make_shared<Lesson>(*lesson));
    }
    return *this;
}

void Submodule::addLesson(std::shared_ptr<Lesson> lesson)
{
    lessons.push_back(lesson);
}

void Submodule::save()
{
    Model::save();

    for (auto& lesson : lessons) {
        lesson->setSubmoduleId(id);
        lesson->save();
    }
}

bool Submodule::update()
{
    if (id < 0)
        return false;

    bool isChanged = false;

    QSqlQuery selectQuery;
    selectQuery.prepare(R"(
                        SELECT name, moduleId FROM main.submodules
                        WHERE id = :id;
                        )");
    selectQuery.bindValue(":id", id);

    if (!selectQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to get Submodule from database"),
            selectQuery.lastError());
    }

    while (selectQuery.next()) {
        bool isOk;
        QString name = selectQuery.value(0).toString();
        int moduleId = selectQuery.value(1).toInt(&isOk);

        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get Submodule moduleId from database"));

        if (getName() != name) {
            isChanged = true;
            setName(name);
        }
        if (getModuleId() != moduleId) {
            isChanged = true;
            setModuleId(moduleId);
        }
    }

    return isChanged;
}

bool Submodule::remove()
{
    if (id < 0)
        return false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare(R"(
                        DELETE FROM main.submodules
                        WHERE id = :id;
                        )");
    deleteQuery.bindValue(":id", id);

    if (!deleteQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to remove Submodule from database"),
            deleteQuery.lastError());
    }

    for (auto& lesson : getLessons())
        lesson->remove();

    id = -1;

    return true;
}

void Submodule::sqlInsert()
{
    if (moduleId < 0)
        throw ModelSavingError("Unable to save Submodule. moduleId must be >= 0");

    QSqlQuery insertQuery;

    insertQuery.prepare(R"(
                        INSERT INTO main.submodules (name, moduleId)
                        VALUES (:name, :moduleId);
                        )");
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":moduleId", moduleId);

    if (!insertQuery.exec())
        throw ModelSavingError(
            "Unable to save Submodule",
            insertQuery.lastError());

    setLastInsertedId(insertQuery);
}

void Submodule::sqlUpdate()
{
    QSqlQuery updateQuery;
    updateQuery.prepare(R"(
                        UPDATE main.submodules
                        SET name = :name
                        WHERE id = :id
                        )");
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":id", id);

    if (!updateQuery.exec())
        throw ModelSavingError(
            "Unable to update Submodule",
            updateQuery.lastError());
}

std::vector<std::shared_ptr<Lesson>>& Submodule::getLessons()
{
    if (id >= 0)
        lessons = Lesson::getBySubmoduleId(id);

    return lessons;
}

QSqlError Submodule::createTable()
{
    QSqlQuery query(R"(
    CREATE TABLE IF NOT EXISTS main.submodules (
                    id integer PRIMARY KEY,
                    name text NOT NULL,
                    moduleId integer,
                    FOREIGN KEY(moduleId) REFERENCES module(id)
                    ON UPDATE CASCADE
                    ON DELETE CASCADE);
                    )");
    QSqlError error;
    if (!query.exec())
        error = query.lastError();

    return error;
}

std::vector<std::shared_ptr<Submodule>> Submodule::getAll()
{
    return filter(-1);
}

std::vector<std::shared_ptr<Submodule>> Submodule::getByModuleId(int moduleId)
{
    return filter(moduleId);
}

std::vector<std::shared_ptr<Submodule>> Submodule::filter(int moduleId)
{
    std::vector<std::shared_ptr<Submodule>> result;

    QString query = R"(
            SELECT id, name, moduleId
            FROM main.submodules
                    )";
    if (moduleId >= 0)
        query += "WHERE moduleId = :moduleId";

    query += ";";

    QSqlQuery selectQuery;
    selectQuery.prepare(query);

    if (moduleId >= 0)
        selectQuery.bindValue(":moduleId", moduleId);

    if (!selectQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to fetch submodules from DB"),
            selectQuery.lastError());
    }

    while (selectQuery.next()) {
        bool isOk;
        int id = selectQuery.value(0).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get id from submodule"));
        QString name = selectQuery.value(1).toString();
        int moduleId = selectQuery.value(2).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get moduleId from submodule"));
        auto submodule = std::make_shared<Submodule>(name);
        submodule->id = id;
        submodule->moduleId = moduleId;
        result.push_back(submodule);
    }

    return result;
}

Submodule::operator QString() const
{
    return name;
}
