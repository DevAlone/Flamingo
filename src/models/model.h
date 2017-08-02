#ifndef MODEL_H
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
