#ifndef LESSONSPARSEREXCEPTION_H
#define LESSONSPARSEREXCEPTION_H

#include "parserexception.h"

class LessonsParserException : public ParserException {
public:
    LessonsParserException(const QString& message);
};

#endif // LESSONSPARSEREXCEPTION_H
