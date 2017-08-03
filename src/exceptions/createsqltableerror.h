#ifndef CREATESQLTABLEERROR_H
#define CREATESQLTABLEERROR_H

#include "databaseinitializationerror.h"

#include <QSqlError>



class CreateSqlTableError : public DatabaseInitializationError
{
public:
    CreateSqlTableError(const QString& message, QSqlError sqlError);

private:
    QSqlError sqlError;
};

#endif // CREATESQLTABLEERROR_H
