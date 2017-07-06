#include "submodule.h"

Submodule::Submodule(const QString& name)
    : ModuleItem(name)
{
    type = MODULE_ITEM_TYPE::SUBMODULE;
}

void Submodule::addLesson(const Lesson& lesson)
{
    lessons.push_back(lesson);
}
