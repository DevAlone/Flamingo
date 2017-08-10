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


#ifndef SUBMODULE_H
#define SUBMODULE_H

#include "lesson/include.h"
#include "moduleitem.h"

#include <QSqlError>
#include <memory>
#include <vector>

class Submodule : public ModuleItem {
public:
    Submodule(const QString& name);
    Submodule(const Submodule& other);
    Submodule& operator=(const Submodule& other);
    virtual operator QString() const;

    void addLesson(std::shared_ptr<Lesson> lesson);

    virtual void save();
    virtual bool update();
    virtual bool remove();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    std::vector<std::shared_ptr<Lesson>>& getLessons();

    static QSqlError createTable();
    static std::vector<std::shared_ptr<Submodule>> getAll();
    static std::vector<std::shared_ptr<Submodule>> getByModuleId(int moduleId);
    static std::vector<std::shared_ptr<Submodule>> filter(int moduleId = -1);

private:
    std::vector<std::shared_ptr<Lesson>> lessons;
};

#endif // SUBMODULE_H
