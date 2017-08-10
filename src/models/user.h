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


#define USERMODEL_H

#include "model.h"

#include <QObject>

#include <QSqlError>
#include <memory>
#include <models/course.h>
#include <vector>

class User : public Model {
public:
    User();
    virtual operator QString() const;

    QString getName() const;
    void setName(const QString& name);

    static QSqlError createTable();
    static std::vector<std::shared_ptr<User>> getAll();

    static void setActiveUserId(int userId);
    static int getActiveUserId();
    static std::shared_ptr<User> getActiveUser();

    virtual void save();
    virtual bool update();
    virtual bool remove();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    std::vector<std::shared_ptr<Course>>& getCourses();

protected:
    QString name = "";
    std::vector<std::shared_ptr<Course>> courses;
};
struct UserPrivate {

    static int activeUserId;
    static std::shared_ptr<User> activeUser;
};

#endif // USERMODEL_H
