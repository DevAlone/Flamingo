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
