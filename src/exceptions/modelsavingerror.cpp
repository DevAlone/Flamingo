#include "modelsavingerror.h"

ModelSavingError::ModelSavingError(const QString& message, const QSqlError& sqlError)
    : message(message)
    , sqlError(sqlError)
{
}
