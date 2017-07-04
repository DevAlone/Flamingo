#include "parseerrorexception.h"

ParseErrorException::ParseErrorException(const QString& message, unsigned stringNumber)
    : ParserException(message)
    , stringNumber(stringNumber)
{
}
