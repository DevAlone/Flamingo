#include "modelsqlerror.h"

ModelSqlError::ModelSqlError(const QString &message, const QSqlError &sqlError)
    :ModelError(message),
      sqlError(sqlError)
{

}
