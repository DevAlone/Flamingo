#include "modulelistdispatcher.h"

#include <models/module.h>

ModuleListDispatcher::ModuleListDispatcher()
{
}

std::vector<std::shared_ptr<Model>> ModuleListDispatcher::getItemList()
{
    int userId = -1;
    if (activeFilter) {
        ModuleListDispatcherFilter* filter = activeFilter.get();
        ModuleListDispatcherCourseIdFilter* courseIdFilter
            = dynamic_cast<ModuleListDispatcherCourseIdFilter*>(filter);

        if (courseIdFilter)
            userId = courseIdFilter->courseId;
    }

    auto modules = Module::filter(userId);
    std::vector<std::shared_ptr<Model>> models;

    for (auto& module : modules)
        models.push_back(module);

    return models;
}

void ModuleListDispatcher::setFilter(std::unique_ptr<ModuleListDispatcherFilter>&& filter)
{
    activeFilter = std::move(filter);
}

void ModuleListDispatcher::resetFilters()
{
    activeFilter.reset();
}

void ModuleListDispatcher::setCourseIdFilter(int courseId)
{
    activeFilter.reset(new ModuleListDispatcherCourseIdFilter(courseId));
}
