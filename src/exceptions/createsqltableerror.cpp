#include "createsqltableerror.h"

CreateSqlTableError::CreateSqlTableError(const QString &message, QSqlError sqlError)
    : DatabaseInitializationError(message)
    , sqlError(sqlError)
{
    this->message += ": " + sqlError.text();
}
