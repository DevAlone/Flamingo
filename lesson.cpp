#include "lesson.h"

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

Nullable<unsigned char> Lesson::getLevel() const
{
    return level;
}

void Lesson::setLevel(unsigned char value)
{
    level = value;
}
