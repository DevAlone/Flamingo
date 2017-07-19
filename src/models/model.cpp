#include "model.h"

#include <QtCore>
#include <QtSql>

#include <exceptions/modelsavingerror.h>

Model::Model()
{
}

Model::~Model()
{
}

int Model::getId() const
{
    return id;
}

void Model::save()
{
    if (id < 0)
        sqlInsert();
    else
        sqlUpdate();
}

void Model::setLastInsertedId(const QSqlQuery& query)
{
    auto lastId = query.lastInsertId();
    if (!lastId.isValid()) {
        throw ModelSavingError(
            "Unable to get last inserted id",
            query.lastError());
    }

    bool isOk;
    id = lastId.toInt(&isOk);
    if (!isOk)
        throw ModelSavingError(
            "Unable to cast last inserted id to int");
}
