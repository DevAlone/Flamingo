// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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

std::vector<std::shared_ptr<ModuleItem>>& Module::getModuleItems()
{
    if (id >= 0) {
        moduleItems = ModuleItem::getByModuleId(id);
    }
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

bool Module::update()
{
    if (id < 0)
        return false;

    bool isChanged = false;

    QSqlQuery selectQuery;
    selectQuery.prepare(R"(
                        SELECT name, level, description, courseId FROM main.modules
                        WHERE id = :id;
                        )");
    selectQuery.bindValue("id", id);

    if (!selectQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to get Module from database"),
            selectQuery.lastError());
    }

    while (selectQuery.next()) {
        bool isOk;
        QString name = selectQuery.value(0).toString();
        int level = selectQuery.value(1).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get Module level from DB"));
        QString description = selectQuery.value(2).toString();
        int courseId = selectQuery.value(3).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get Module courseId from DB"));

        if (getName() != name) {
            isChanged = true;
            setName(name);
        }
        if (getLevel() != level) {
            isChanged = true;
            setLevel(level);
        }
        if (getDescription() != description) {
            isChanged = true;
            setDescription(description);
        }
        if (getCourseId() != courseId) {
            isChanged = true;
            setCourseId(courseId);
        }
    }

    return isChanged;
}

bool Module::remove()
{
    if (id < 0)
        return false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare(R"(
                        DELETE FROM main.modules
                        WHERE id = :id;
                        )");
    deleteQuery.bindValue(":id", id);

    if (!deleteQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to remove Module from database"),
            deleteQuery.lastError());
    }

    for (auto& moduleItem : getModuleItems())
        moduleItem->remove();

    id = -1;

    return true;
}

void Module::sqlInsert()
{
    if (courseId < 0)
        throw ModelSavingError("Unable to save module. courseId must be >= 0");

    QSqlQuery insertQuery;

    insertQuery.prepare(R"(
                        INSERT INTO main.modules (name, courseId, level, description)
                        VALUES (:name, :courseId, :level, :description);
                        )");
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":courseId", courseId);
    insertQuery.bindValue(":level", level);
    insertQuery.bindValue(":description", description);

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
                        SET name = :name, courseId = :courseId, level = :level, description = :description
                        WHERE id=:id;
                        )");
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":id", id);
    updateQuery.bindValue(":courseId", courseId);
    updateQuery.bindValue(":level", level);
    updateQuery.bindValue(":description", description);

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
                    level integer NOT NULL,
                    description text NOT NULL,
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

std::vector<std::shared_ptr<Module>> Module::getAll()
{
    return filter(-1);
}

std::vector<std::shared_ptr<Module>> Module::getByCourseId(int courseId)
{
    return filter(courseId);
}

std::vector<std::shared_ptr<Module>> Module::filter(int courseId)
{
    std::vector<std::shared_ptr<Module>> result;

    QString query = R"(
                    SELECT id, name, level, description, courseId
                    FROM main.modules
                    )";
    if (courseId >= 0)
        query += "WHERE courseId = :courseId";

    query += ";";

    QSqlQuery selectQuery;
    selectQuery.prepare(query);

    if (courseId >= 0)
        selectQuery.bindValue(":courseId", courseId);

    if (!selectQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to fetch modules from DB"),
            selectQuery.lastError());
    }

    while (selectQuery.next()) {
        bool isOk;
        int id = selectQuery.value(0).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get id from module"));
        QString name = selectQuery.value(1).toString();
        int level = selectQuery.value(2).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get level from module"));
        QString description = selectQuery.value(3).toString();
        int courseId = selectQuery.value(4).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get courseId from module"));

        auto module = std::make_shared<Module>(name);
        module->id = id;
        //        module->name = name;
        module->level = level;
        module->description = description;
        module->courseId = courseId;
        result.push_back(module);
    }

    return result;
}

int Module::getLevel() const
{
    return level;
}

void Module::setLevel(int value)
{
    if (value < 1 || value > 10)
        throw ModelError(
            QObject::tr("Unable to set Module level. It must be value from 1 to 10(included)"));

    level = value;
}

QString Module::getDescription() const
{
    return description;
}

void Module::setDescription(const QString& value)
{
    description = value;
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
