#include "lesson.h"

#include <QSqlQuery>

Lesson::Lesson(const QString& name)
    : ModuleItem(name)
{
    type = MODULE_ITEM_TYPE::LESSON;
}

Lesson::operator QString() const
{
    return name;
}

bool Lesson::addPage(std::shared_ptr<Page>& page)
{
    if (pages.find(page->getNumber()) != pages.end()) {
        // if question with same number is already in here
        return false;
    }

    pages.insert(std::make_pair(
        page->getNumber(),
        page));
    return true;
}

std::map<unsigned, std::shared_ptr<Page> >& Lesson::getPages()
{
    return pages;
}

unsigned char Lesson::getLevel() const
{
    return level;
}

void Lesson::setLevel(unsigned char value)
{
    level = value;
}

void Lesson::save()
{
    Model::save();
}

bool Lesson::update()
{
    if (id < 0)
        return false;

    bool isChanged = false;

    QSqlQuery selectQuery;
    selectQuery.prepare(R"(
                SELECT name, moduleId, submoduleId, data FROM main.lessons
                WHERE id = :id;
                )");
    selectQuery.bindValue(":id", id);

    if (!selectQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to get Lesson data from database"),
            selectQuery.lastError());
    }

    while (selectQuery.next()) {
        bool isOk;
        QString name = selectQuery.value(0).toString();
        int moduleId = selectQuery.value(1).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get Lessons moduleId from database"));
        int submoduleId = selectQuery.value(2).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get Lessons submoduleId from database"));

        QString data = selectQuery.value(3).toString();

        if (getName() != name) {
            isChanged = true;
            setName(name);
        }
        if (getModuleId() != moduleId) {
            isChanged = true;
            setModuleId(moduleId);
        }
        if (getSubmoduleId() != submoduleId) {
            isChanged = true;
            setSubmoduleId(submoduleId);
        }
    }

    return isChanged;
}

void Lesson::sqlInsert()
{
    if (moduleId < 0 && submoduleId < 0)
        throw ModelSavingError(
            "Unable to save Lesson. moduleId or submoduleId must be >= 0");

    QSqlQuery insertQuery;

    insertQuery.prepare(R"(
                        INSERT INTO main.lessons (name, moduleId, submoduleId, data)
                        VALUES (:name, :moduleId, :submoduleId, :data);
                        )");
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":moduleId", moduleId);
    insertQuery.bindValue(":submoduleId", submoduleId);
    insertQuery.bindValue(":data", serialize());

    if (!insertQuery.exec())
        throw ModelSavingError(
            "Unable to save Lesson",
            insertQuery.lastError());

    setLastInsertedId(insertQuery);
}

void Lesson::sqlUpdate()
{
    QSqlQuery updateQuery;
    updateQuery.prepare(R"(
                        UPDATE main.lessons
                        SET name = :name, moduleId = :moduleId, submoduleId = :submoduleId, data = :data
                        WHERE id = :id;
                        )");
    updateQuery.bindValue(":name", name);
    updateQuery.bindValue(":moduleId", moduleId);
    updateQuery.bindValue(":submoduleId", submoduleId);
    updateQuery.bindValue(":data", serialize());
    updateQuery.bindValue(":id", id);

    if (!updateQuery.exec())
        throw ModelSavingError(
            "Unable to update Lesson",
            updateQuery.lastError());
}

void Lesson::setSubmoduleId(int value)
{
    submoduleId = value;
}

int Lesson::getSubmoduleId() const
{
    return submoduleId;
}

QSqlError Lesson::createTable()
{
    QSqlQuery query(R"(
                    CREATE TABLE IF NOT EXISTS main.lessons (
                    id integer PRIMARY KEY,
                    name text NOT NULL,
                    moduleId integer,
                    submoduleId integer,
                    data text NOT NULL,
                    FOREIGN KEY(moduleId) REFERENCES module(id)
                    ON UPDATE CASCADE
                    ON DELETE CASCADE,
                    FOREIGN KEY(submoduleId) REFERENCES submodule(id)
                    ON UPDATE CASCADE
                    ON DELETE CASCADE);
                    )");
    QSqlError error;
    if (!query.exec())
        error = query.lastError();

    return error;
}

QString Lesson::serialize()
{
    // TODO: do it!
    return "";
}

Lesson Lesson::deserialize(const QString& data, const QString& name)
{
    // TODO: do it!
    return Lesson(name);
}
