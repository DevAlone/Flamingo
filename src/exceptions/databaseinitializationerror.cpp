#include "databaseinitializationerror.h"

DatabaseInitializationError::DatabaseInitializationError(const QString &message)
    : Exception(message)
{

}
