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


#ifndef COURSE_H
#define COURSE_H

#include "module.h"

#include <QSqlError>
#include <QString>
#include <QVector>

#include <vector>

#include <models/model.h>

class Course : public Model {
public:
    Course(QString name);
    virtual operator QString() const;

    QString getName() const;
    void setName(const QString& value);
    void addModule(std::shared_ptr<Module> module);
    void addModules(std::vector<std::shared_ptr<Module>>& modules);

    QString getAuthor() const;
    void setAuthor(const QString& value);

    unsigned char getLevel() const;
    void setLevel(int value);

    std::vector<std::shared_ptr<Module>>& getModules();

    int getUserId() const;
    void setUserId(int value);

    virtual void save();
    virtual bool update();
    virtual bool remove();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    static QSqlError createTable();
    static std::vector<std::shared_ptr<Course>> getAll();
    static std::vector<std::shared_ptr<Course>> getByUserId(int userId);
    static std::vector<std::shared_ptr<Course>> filter(int userId = -1);

    QString getLanguageCode() const;
    void setLanguageCode(const QString& value);

    QString getDescription() const;
    void setDescription(const QString& value);

private:
    QString name = "";
    QString author = "";
    unsigned char level = 1;
    QString description = "";
    QString languageCode = "";
    std::vector<std::shared_ptr<Module>> modules;

    int userId = -1;
};

#endif // COURSE_H
