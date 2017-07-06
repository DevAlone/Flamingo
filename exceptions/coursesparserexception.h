#ifndef COURSEPARSEREXCEPTION_H
#define COURSEPARSEREXCEPTION_H

#include "parserexception.h"

class CoursesParserException : public ParserException {
public:
    CoursesParserException(const QString& message);
};

#endif // COURSEPARSEREXCEPTION_H
