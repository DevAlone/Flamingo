#ifndef PARSER_H
#define PARSER_H

#include <QtCore>

class Parser {
public:
    Parser();

    static std::pair<QString, QString> getKeyValueFromString(const QString& str, bool* isOk, QChar delimiter = ':');
};

#endif // PARSER_H
