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
