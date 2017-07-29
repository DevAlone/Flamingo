#ifndef MODELSERIALIZATIONERROR_H
#define MODELSERIALIZATIONERROR_H

#include "exception.h"

#include <QString>

class ModelSerializationError : public Exception
{
public:
    ModelSerializationError(const QString& message);


};

#endif // MODELSERIALIZATIONERROR_H
