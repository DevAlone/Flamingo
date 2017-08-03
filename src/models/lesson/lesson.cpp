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

std::map<unsigned, std::shared_ptr<Page>>& Lesson::getPages()
{
    return pages;
}

std::pair<size_t, size_t> Lesson::getCompleteness()
{
    // TODO: optimize:
    std::pair<size_t, size_t> result;
    result.first = result.second = 0;

    for (auto& pagePair : pages) {
        result.first += pagePair.second->getCompleteness(); // 0-100
        result.second += 100;
    }
    return result;
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

        updateSerializedData(data);
    }

    return isChanged;
}

bool Lesson::remove()
{
    if (id < 0)
        return false;

    QSqlQuery deleteQuery;
    deleteQuery.prepare(R"(
                        DELETE FROM main.lessons
                        WHERE id = :id;
                        )");
    deleteQuery.bindValue(":id", id);

    if (!deleteQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to remove Lesson from database"),
            deleteQuery.lastError());
    }

    id = -1;

    return true;
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

QString Lesson::getDescription() const
{
    return description;
}

void Lesson::setDescription(const QString& value)
{
    description = value;
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

std::vector<std::shared_ptr<Lesson>> Lesson::getAll()
{
    return filter(-1, -1);
}

std::vector<std::shared_ptr<Lesson>> Lesson::getByModuleId(int moduleId)
{
    return filter(moduleId, -1);
}

std::vector<std::shared_ptr<Lesson>> Lesson::getBySubmoduleId(int submoduleId)
{
    return filter(-1, submoduleId);
}

std::vector<std::shared_ptr<Lesson>> Lesson::filter(int moduleId, int submoduleId)
{
    if (moduleId >= 0 && submoduleId >= 0)
        throw ModelError(
            QObject::tr("Logic error. You cannot get lesson with both moduleId and submoduleId more or equal 0"));

    std::vector<std::shared_ptr<Lesson>> result;

    QString query = R"(
                    SELECT id, name, moduleId, submoduleId, data
            FROM main.lessons
                    )";

    if (moduleId >= 0)
        query += "WHERE moduleId = :moduleId";
    else if (submoduleId >= 0)
        query += "WHERE submoduleId = :submoduleId";

    query += ";";

    QSqlQuery selectQuery;
    selectQuery.prepare(query);

    if (moduleId >= 0)
        selectQuery.bindValue(":moduleId", moduleId);
    else if (submoduleId >= 0)
        selectQuery.bindValue(":submoduleId", submoduleId);

    if (!selectQuery.exec()) {
        throw ModelSqlError(
            QObject::tr("Unable to fetch lessons from DB"),
            selectQuery.lastError());
    }

    while (selectQuery.next()) {
        bool isOk;

        int id = selectQuery.value(0).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get id from lesson"));
        QString name = selectQuery.value(1).toString();
        int moduleId = selectQuery.value(2).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get moduleId from lesson"));
        int submoduleId = selectQuery.value(3).toInt(&isOk);
        if (!isOk)
            throw ModelError(
                QObject::tr("Unable to get submoduleId from lesson"));
        QString data = selectQuery.value(4).toString();

        auto lesson = deserialize(data, name);
        lesson->id = id;
        lesson->moduleId = moduleId;
        lesson->submoduleId = submoduleId;
        result.push_back(lesson);
    }

    return result;
}

QString Lesson::serialize()
{
    QJsonObject obj;

    QJsonArray jsonPages;

    for (auto& page : pages) {
        auto pageJsonObject = page.second->toJsonObject();

        jsonPages.push_back(QJsonObject{
            { "page_number", QString::number(page.first) },
            { "page", pageJsonObject } });
    }
    obj["pages"] = jsonPages;

    QJsonDocument doc(obj);

    return doc.toJson(QJsonDocument::Compact);
}

std::shared_ptr<Lesson> Lesson::deserialize(const QString& data, const QString& name)
{
    std::shared_ptr<Lesson> lesson = std::make_shared<Lesson>(name);

    QJsonObject obj;

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(), &error);

    if (doc.isNull())
        throw ModelError(
            QObject::tr("Unable to parse json in lesson object: ")
            + error.errorString());

    if (!doc.isObject())
        throw ModelError(
            QObject::tr("Unable to parse json in lesson object: json document is not an object"));

    obj = doc.object();

    QJsonArray pages;
    if (obj["pages"].isArray())
        pages = obj["pages"].toArray();
    else
        throw ModelError(
            QObject::tr("Unable to parse json in lesson object: "
                        "pages is not exist or is not an array"));

    for (auto jsonPage : pages) {
        QJsonObject jsonPagePair;

        if (jsonPage.isObject())
            jsonPagePair = jsonPage.toObject();
        else
            throw ModelError(
                QObject::tr("Unable to parse json in lesson object: "
                            "jsonPage doesn't exist or is not an object"));

        // parse page
        std::pair<unsigned, std::shared_ptr<Page>> pagePair;

        if (jsonPagePair["page_number"].isString()) {
            QString str = jsonPagePair["page_number"].toString();
            bool isOk;
            unsigned number = str.toUInt(&isOk);
            if (!isOk)
                throw ModelError(
                    QObject::tr("Unable to parse json in lesson object: "
                                "page_number isn't an unsigned number"));
            pagePair.first = number;
        } else
            throw ModelError(
                QObject::tr("Unable to parse json in lesson object: "
                            "page_number doesn't exist or isn't a string"));

        if (jsonPagePair["page"].isObject()) {
            pagePair.second = Page::fromJsonObject(jsonPagePair["page"].toObject());
        } else
            throw ModelError(
                QObject::tr("Unable to parse json in lesson object: "
                            "page doesn't exist or isn't an object"));

        // add page to map
        if (lesson->pages.find(pagePair.first) != lesson->pages.end())
            throw ModelError(
                QObject::tr("Unable to deserialize lesson: "
                            "attempting to add more than one lesson with same number"));

        lesson->pages.insert(pagePair);
    }

    return lesson;
}

void Lesson::updateSerializedData(const QString& data)
{
    std::shared_ptr<Lesson> lesson = deserialize(data, "");

    pages = lesson->pages;
}
