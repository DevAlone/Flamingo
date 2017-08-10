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


#define MODEL_H

#include "exceptions/modelsavingerror.h"

#include <QSqlQuery>

#include <QString>

class Model {
public:
    Model();
    virtual ~Model();

    int getId() const;

    // save model to database
    // method creates new instance if id < 0 or updates existent if id >= 0
    virtual void save();
    // update from database
    // if id < 0 method returns false
    // if id >= 0 method gets data from DB
    // and update corresponding fields on model
    // return true if model was changed
    virtual bool update() = 0;
    // function return true if object was removed
    // function can return false when object
    // wasn't store in database
    virtual bool remove() = 0;

    virtual operator QString() const = 0;

protected:
    int id = -1;
    virtual void sqlInsert() = 0;
    virtual void sqlUpdate() = 0;
    void setLastInsertedId(const QSqlQuery& query);
};

#endif // MODEL_H
