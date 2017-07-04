#ifndef PARSEERROREXCEPTION_H
#define PARSEERROREXCEPTION_H

#include "parserexception.h"

#include <QString>

class ParseErrorException : public ParserException {
public:
    ParseErrorException(const QString& message, unsigned stringNumber);

private:
    const unsigned stringNumber;
};

#endif // PARSEERROREXCEPTION_H
