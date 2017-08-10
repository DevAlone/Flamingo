#include "modelsavingerror.h"

ModelSavingError::ModelSavingError(const QString& message, const QSqlError& sqlError)
    : ModelSqlError(message, sqlError)
{
}
