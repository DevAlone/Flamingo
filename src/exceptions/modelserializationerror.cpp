#include "modelserializationerror.h"

ModelSerializationError::ModelSerializationError(const QString &message)
    : Exception(message)
{
    this->message = "Error during serialization/deserialization model: " + message;
}
