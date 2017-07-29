#include "exception.h"

Exception::Exception(const QString& message)
{
}

Exception::~Exception()
{
}

const QString& Exception::getMessage() const
{
    return message;
}
