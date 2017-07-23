#ifndef MODULESPARSER_H
#define MODULESPARSER_H

#include "logger/parserlogger.h"
#include "models/include.h"
#include "parser.h"

#include <QtCore>

namespace parser {
class ModulesParser : public Parser {
public:
    std::vector<std::shared_ptr<Module>> parseDirectory(const QString& path);

    std::shared_ptr<Module> parseModule(const QString& modulePath);

private:
};
}

#endif // MODULESPARSER_H
