#include "modelerror.h"

ModelError::ModelError(const QString& message)
    : Exception(message)
{
}
