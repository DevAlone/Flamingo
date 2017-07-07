#include "parser.h"

Parser::Parser()
{
}

std::pair<QString, QString> Parser::getKeyValueFromString(const QString& str, bool* isOk, QChar delimiter)
{
    int indexOfDelimiter = str.indexOf(delimiter);
    if (indexOfDelimiter < 0) {
        *isOk = false;
        return std::pair<QString, QString>();
    }
    *isOk = true;
    return std::make_pair(
        str.left(indexOfDelimiter).simplified().toLower(),
        str.mid(indexOfDelimiter + 1).trimmed());
}
