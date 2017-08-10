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
