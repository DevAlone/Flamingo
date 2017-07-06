#include "parserexception.h"

ParserException::ParserException(const QString& message)
    : message(message)
{
}

const QString& ParserException::getMessage() const
{
    return message;
}
