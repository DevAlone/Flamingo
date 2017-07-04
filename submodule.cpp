#include "submodule.h"

Submodule::Submodule(const QString& name)
    : ModuleItem(name)
{
}

void Submodule::addLesson(const Lesson& lesson)
{
    lessons.push_back(lesson);
}
