#ifndef COURSEPARSEREXCEPTION_H
#define COURSEPARSEREXCEPTION_H

#include "parserexception.h"

class CourseParserException : public ParserException {
public:
    CourseParserException(const QString& message);
};

#endif // COURSEPARSEREXCEPTION_H
