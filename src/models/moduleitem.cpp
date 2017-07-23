#include "moduleitem.h"
#include "submodule.h"

#include <algorithm>

ModuleItem::ModuleItem(const QString& name)
    : name(name)
{
}

ModuleItem::~ModuleItem()
{
}

QString ModuleItem::getName() const
{
    return name;
}

void ModuleItem::setName(const QString& value)
{
    name = value;
}

MODULE_ITEM_TYPE ModuleItem::getType() const
{
    return type;
}

int ModuleItem::getModuleId() const
{
    return moduleId;
}

void ModuleItem::setModuleId(int value)
{
    moduleId = value;
}

std::vector<std::shared_ptr<ModuleItem>> ModuleItem::getAll()
{
    return filter(-1);
}

std::vector<std::shared_ptr<ModuleItem>> ModuleItem::getByModuleId(int moduleId)
{
    return filter(moduleId);
}

std::vector<std::shared_ptr<ModuleItem>> ModuleItem::filter(int moduleId)
{
    std::vector<std::shared_ptr<ModuleItem>> result;

    auto submodules = Submodule::filter(moduleId);
    auto lessons = Lesson::filter(moduleId, -1);

    for (auto& submodule : submodules)
        result.push_back(submodule);

    for (auto& lesson : lessons)
        result.push_back(lesson);

    std::sort(result.begin(), result.end(), [](const auto& moduleItemPtrLeft, const auto& moduleItemPtrRight) {
        // TODO: check it
        return moduleItemPtrLeft->getName() > moduleItemPtrRight->getName();
    });

    return result;
}
