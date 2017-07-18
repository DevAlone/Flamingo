#include "lesson.h"

#include <QSqlQuery>

Lesson::Lesson(const QString& name)
    : ModuleItem(name)
{
    type = MODULE_ITEM_TYPE::LESSON;
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
    // TODO: serialize and save
}

QSqlError Lesson::createTable()
{
    QSqlQuery query(R"(
    CREATE TABLE IF NOT EXISTS main.lessons (
                    id integer PRIMARY KEY,
                    level integer NOT NULL,
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
