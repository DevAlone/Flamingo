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


#ifndef MODULEITEM_H
#define MODULEITEM_H

#include "model.h"

#include <QString>

#include <memory>
#include <vector>

enum class MODULE_ITEM_TYPE {
    NONE,
    SUBMODULE,
    LESSON
};

class ModuleItem : public Model {
public:
    ModuleItem(const QString& name);
    virtual ~ModuleItem();

    QString getName() const;
    void setName(const QString& value);

    MODULE_ITEM_TYPE getType() const;

    // TODO:    virtual void save() = 0;

    int getModuleId() const;
    void setModuleId(int value);

    static std::vector<std::shared_ptr<ModuleItem>> getAll();
    static std::vector<std::shared_ptr<ModuleItem>> getByModuleId(int moduleId);
    static std::vector<std::shared_ptr<ModuleItem>> filter(int moduleId = -1);

protected:
    QString name = "";
    MODULE_ITEM_TYPE type = MODULE_ITEM_TYPE::NONE;
    int moduleId = -1;
};

#endif // MODULEITEM_H
