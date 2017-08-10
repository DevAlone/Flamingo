#include "moduleitemtreedispatcher.h"

#include <models/moduleitem.h>
#include <models/submodule.h>

#include <algorithm>

ModuleItemTreeDispatcher::ModuleItemTreeDispatcher()
{
}

std::vector<ModelTreeDispatcherItem> ModuleItemTreeDispatcher::getItemTree()
{
    int moduleId = -1;
    if (activeFilter) {
        auto moduleIdFilter = dynamic_cast<ModuleItemTreeDispatcherModuleIdFilter*>(
            activeFilter.get());

        if (moduleIdFilter)
            moduleId = moduleIdFilter->moduleId;
    }

    std::vector<ModelTreeDispatcherItem> result;

    std::vector<std::shared_ptr<Submodule>> submodules = Submodule::filter(moduleId);

    for (auto& submodule : submodules) {
        ModelTreeDispatcherItem submoduleTreeItem;
        submoduleTreeItem.item = submodule;

        auto lessons = Lesson::filter(-1, submodule->getId());

        for (auto& lesson : lessons) {
            ModelTreeDispatcherItem lessonTreeItem;
            lessonTreeItem.item = lesson;

            submoduleTreeItem.children.push_back(lessonTreeItem);
        }

        result.push_back(submoduleTreeItem);
    }

    std::vector<std::shared_ptr<Lesson>> lessons = Lesson::filter(moduleId, -1);

    for (auto& lesson : lessons) {
        ModelTreeDispatcherItem lessonTreeItem;
        lessonTreeItem.item = lesson;

        result.push_back(lessonTreeItem);
    }
    // TODO: sort
    std::sort(result.begin(), result.end(), [](const auto& left, const auto& right) {
        return QString(*left.item) < QString(*right.item);
    });

    return result;
}

void ModuleItemTreeDispatcher::setFilter(std::unique_ptr<ModuleItemTreeDispatcherFilter>&& filter)
{
    activeFilter = std::move(filter);
}

void ModuleItemTreeDispatcher::resetFilters()
{
    activeFilter.reset();
}

void ModuleItemTreeDispatcher::setModuleIdFilter(int moduleId)
{
    activeFilter.reset(new ModuleItemTreeDispatcherModuleIdFilter(moduleId));
}
