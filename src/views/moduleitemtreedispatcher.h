// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
