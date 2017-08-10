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
