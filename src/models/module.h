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


#define MODULE_H

#include "moduleitem.h"

#include <QSqlError>
#include <memory>
#include <vector>

#include <models/model.h>

class Module : public Model {
public:
    Module(const QString& name);
    Module(const Module& other);
    Module& operator=(const Module& other);
    virtual operator QString() const;

    QString getName() const;
    void setName(const QString& value);

    void addModuleItem(std::shared_ptr<ModuleItem> moduleItem);

    std::vector<std::shared_ptr<ModuleItem>>& getModuleItems();

    int getCourseId() const;
    void setCourseId(int value);

    virtual void save();
    virtual bool update();
    virtual bool remove();
    virtual void sqlInsert();
    virtual void sqlUpdate();
    static QSqlError createTable();
    static std::vector<std::shared_ptr<Module>> getAll();
    static std::vector<std::shared_ptr<Module>> getByCourseId(int courseId);
    static std::vector<std::shared_ptr<Module>> filter(int courseId = -1);

    int getLevel() const;
    void setLevel(int value);

    QString getDescription() const;
    void setDescription(const QString& value);

private:
    QString name = "";
    unsigned char level = 1;
    QString description = "";
    std::vector<std::shared_ptr<ModuleItem>> moduleItems;

    int courseId = -1;
};

#endif // MODULE_H
