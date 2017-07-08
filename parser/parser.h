#ifndef PARSER_H
#define PARSER_H

#include <QtCore>

namespace parser {
std::pair<QString, QString> getKeyValueFromString(const QString& str, bool* isOk, QChar delimiter = ':');
}

#endif // PARSER_H
