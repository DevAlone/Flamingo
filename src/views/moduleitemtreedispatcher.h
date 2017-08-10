#ifndef MODULEITEMTREEDISPATCHER_H
#define MODULEITEMTREEDISPATCHER_H

#include "modeltreedispatcher.h"

class ModuleItemTreeDispatcherFilter;
class ModuleItemTreeDispatcherEqualFilter;
class ModuleItemTreeDispatcherModuleIdFilter;

class ModuleItemTreeDispatcher : public ModelTreeDispatcher {
public:
    ModuleItemTreeDispatcher();

    virtual std::vector<ModelTreeDispatcherItem> getItemTree();

    void setFilter(std::unique_ptr<ModuleItemTreeDispatcherFilter>&& filter);
    void resetFilters();
    void setModuleIdFilter(int moduleId);

private:
    // std::vector should be here
    std::unique_ptr<ModuleItemTreeDispatcherFilter> activeFilter;
};

class ModuleItemTreeDispatcherFilter {
    friend class ModuleItemTreeDispatcher;

public:
    virtual ~ModuleItemTreeDispatcherFilter() = default;
};

class ModuleItemTreeDispatcherEqualFilter : public ModuleItemTreeDispatcherFilter {
    friend class ModuleItemTreeDispatcher;
};

class ModuleItemTreeDispatcherModuleIdFilter : public ModuleItemTreeDispatcherEqualFilter {
    friend class ModuleItemTreeDispatcher;

public:
    ModuleItemTreeDispatcherModuleIdFilter(int moduleId)
        : moduleId(moduleId)
    {
    }

private:
    int moduleId;
};

#endif // MODULEITEMTREEDISPATCHER_H
