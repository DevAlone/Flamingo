#ifndef MODULESPARSEREXCEPTION_H
#define MODULESPARSEREXCEPTION_H

#include "parserexception.h"

class ModulesParserException : public ParserException {
public:
    ModulesParserException(const QString& message);
};

#endif // MODULESPARSEREXCEPTION_H
