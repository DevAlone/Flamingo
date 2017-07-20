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

    virtual void save();

    virtual operator QString() const = 0;

protected:
    int id = -1;
    virtual void sqlInsert() = 0;
    virtual void sqlUpdate() = 0;
    void setLastInsertedId(const QSqlQuery& query);
};

#endif // MODEL_H
