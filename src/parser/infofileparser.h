#ifndef INFOFILEPARSER_H
#define INFOFILEPARSER_H

#include "parser.h"

namespace parser {
class InfoFileParser : public Parser {
public:
    std::map<QString, QString> parseFile(const QString& path);
};
}

#endif // INFOFILEPARSER_H
