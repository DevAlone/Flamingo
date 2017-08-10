#pragma once

#include "modellistdispatcher.h"

class ModuleListDispatcherFilter;
class ModuleListDispatcherEqualFilter;
class ModuleListDispatcherCourseIdFilter;

class ModuleListDispatcher : public ModelListDispatcher {
public:
    ModuleListDispatcher();

    virtual std::vector<std::shared_ptr<Model>> getItemList();

    void setFilter(std::unique_ptr<ModuleListDispatcherFilter>&& filter);
    void resetFilters();
    void setCourseIdFilter(int courseId);

private:
    // std::vector should be here
    std::unique_ptr<ModuleListDispatcherFilter> activeFilter;
};

class ModuleListDispatcherFilter {
    friend class ModuleListDispatcher;

public:
    virtual ~ModuleListDispatcherFilter() = default;
};
class ModuleListDispatcherEqualFilter : public ModuleListDispatcherFilter {
    friend class ModuleListDispatcher;

public:
};
class ModuleListDispatcherCourseIdFilter : public ModuleListDispatcherEqualFilter {
    friend class ModuleListDispatcher;

public:
    ModuleListDispatcherCourseIdFilter(int courseId)
        : courseId(courseId)
    {
    }

private:
    int courseId;
};
