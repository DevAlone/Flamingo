#ifndef MODULEDISPATCHER_H
#define MODULEDISPATCHER_H

#include "modeldispatcher.h"

class ModuleDispatcherFilter;
class ModuleDispatcherEqualFilter;
class ModuleDispatcherCourseIdFilter;

class ModuleDispatcher : public ModelDispatcher {
public:
    ModuleDispatcher();

    virtual std::vector<std::shared_ptr<Model>> getItems();

    void setFilter(std::unique_ptr<ModuleDispatcherFilter>&& filter);
    void resetFilters();
    void setCourseIdFilter(int courseId);

private:
    // std::vector should be here
    std::unique_ptr<ModuleDispatcherFilter> activeFilter;
};

class ModuleDispatcherFilter {
    friend class ModuleDispatcher;

public:
    virtual ~ModuleDispatcherFilter() = default;
};
class ModuleDispatcherEqualFilter : public ModuleDispatcherFilter {
    friend class ModuleDispatcher;

public:
};
class ModuleDispatcherCourseIdFilter : public ModuleDispatcherEqualFilter {
    friend class ModuleDispatcher;

public:
    ModuleDispatcherCourseIdFilter(int courseId)
        : courseId(courseId)
    {
    }

private:
    int courseId;
};

#endif // MODULEDISPATCHER_H
