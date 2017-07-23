#include "moduledispatcher.h"

#include <models/module.h>

ModuleDispatcher::ModuleDispatcher()
{
}

std::vector<std::shared_ptr<Model>> ModuleDispatcher::getItems()
{
    int userId = -1;
    if (activeFilter) {
        ModuleDispatcherFilter* filter = activeFilter.get();
        ModuleDispatcherCourseIdFilter* courseIdFilter
            = dynamic_cast<ModuleDispatcherCourseIdFilter*>(filter);

        if (courseIdFilter)
            userId = courseIdFilter->courseId;
    }

    auto modules = Module::filter(userId);
    std::vector<std::shared_ptr<Model>> models;

    for (auto& module : modules)
        models.push_back(module);

    return models;
}

void ModuleDispatcher::setFilter(std::unique_ptr<ModuleDispatcherFilter>&& filter)
{
    activeFilter = std::move(filter);
}

void ModuleDispatcher::resetFilters()
{
    activeFilter.reset();
}

void ModuleDispatcher::setCourseIdFilter(int courseId)
{
    activeFilter.reset(new ModuleDispatcherCourseIdFilter(courseId));
}
