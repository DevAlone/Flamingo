#ifndef INFOFILEPARSER_H
#define INFOFILEPARSER_H

#include "parser.h"

namespace parser {
class InfoSectionParser : public Parser {
public:
    std::map<QString, QString> parseInfoFile(const QString& path);

    std::map<QString, QString> parseInfoSection(QString& data, const QString& path = "");

private:
};
}

#endif // INFOFILEPARSER_H
