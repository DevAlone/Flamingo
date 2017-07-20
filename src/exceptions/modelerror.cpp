#include "modelerror.h"

ModelError::ModelError(const QString& message)
    : message(message)
{
}

const QString& ModelError::getMessage() const
{
    return message;
}
