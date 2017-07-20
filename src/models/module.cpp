#include "module.h"
#include "submodule.h"

#include <QSqlQuery>

#include <exceptions/modelsavingerror.h>

Module::Module(const QString& name)
    : name(name)
{
}

Module::Module(const Module& other)
    : name(other.name)
    , courseId(other.courseId)
{
    moduleItems.clear();
    for (auto& moduleItem : other.moduleItems) {
        MODULE_ITEM_TYPE type = moduleItem->getType();
        switch (type) {
        case MODULE_ITEM_TYPE::SUBMODULE:
            moduleItems.push_back(
                std::shared_ptr<Submodule>(new Submodule((const Submodule&)(*moduleItem))));
            break;
        case MODULE_ITEM_TYPE::LESSON:
            moduleItems.push_back(
                std::shared_ptr<Lesson>(new Lesson((const Lesson&)(*moduleItem))));
            break;
        }
    }
}

Module& Module::operator=(const Module& other)
{
    name = other.name;
    courseId = other.courseId;
    for (auto& moduleItem : other.moduleItems) {
        MODULE_ITEM_TYPE type = moduleItem->getType();
        switch (type) {
        case MODULE_ITEM_TYPE::SUBMODULE:
            moduleItems.push_back(
                std::shared_ptr<Submodule>(new Submodule((const Submodule&)(*moduleItem))));
            break;
        case MODULE_ITEM_TYPE::LESSON:
            moduleItems.push_back(
                std::shared_ptr<Lesson>(new Lesson((const Lesson&)(*moduleItem))));
            break;
        }
    }
    return *this;
}

QString Module::getName() const
{
    return name;
}

void Module::setName(const QString& value)
{
    name = value;
}

void Module::addModuleItem(std::shared_ptr<ModuleItem> moduleItem)
{
    moduleItems.push_back(moduleItem);
}

std::vector<std::shared_ptr<ModuleItem> >& Module::getModuleItems()
{
    return moduleItems;
}

void Module::save()
{
    Model::save();

    for (auto& moduleItem : moduleItems) {
        moduleItem->setModuleId(id);
        moduleItem->save();
    }
}

void Module::sqlInsert()
{
    if (courseId < 0)
        throw ModelSavingError("Unable to save module. courseId must be >= 0");

    QSqlQuery insertQuery;

    insertQuery.prepare(R"(
                        INSERT INTO main.modules (name, courseId)
                        VALUES (:name, :courseId);
                        )");
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":courseId", courseId);

    if (!insertQuery.exec())
        throw ModelSavingError(
            "Unable to save Module",
            insertQuery.lastError());

    setLastInsertedId(insertQuery);
}

void Module::sqlUpdate()
{
    QSqlQuery updateQuery;
    updateQuery.prepare(R"(
                        UPDATE main.modules
                        SET name = :name
                        WHERE id=:id;
                        )");
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":id", id);

    if (!updateQuery.exec())
        throw ModelSavingError(
            "Unable to update Module",
            updateQuery.lastError());
}

QSqlError Module::createTable()
{
    QSqlQuery query(R"(
    CREATE TABLE IF NOT EXISTS main.modules (
                    id integer PRIMARY KEY,
                    name text NOT NULL,
                    courseId integer,
                    FOREIGN KEY(courseId) REFERENCES courses(id)
                    ON UPDATE CASCADE
                    ON DELETE CASCADE);
                    )");
    QSqlError error;
    if (!query.exec())
        error = query.lastError();

    return error;
}

int Module::getCourseId() const
{
    return courseId;
}

void Module::setCourseId(int value)
{
    courseId = value;
}

Module::operator QString() const
{
    return name;
}
