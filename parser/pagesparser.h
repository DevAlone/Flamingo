#ifndef PAGESPARSER_H
#define PAGESPARSER_H

#include "parser.h"

#include <page.h>

namespace parser {
class PagesParser : public Parser {
public:
    PagesParser();

    /// function can return empty smart pointer.
    /// Check it before using.
    std::shared_ptr<Page> parsePage(
        const QString& string,
        unsigned questionNumber,
        unsigned long baseLineNumber);

    enum class SECTION {
        NONE,
        INFO,
        ANSWERS
    };

private:
    SECTION section = SECTION::INFO;
    unsigned long baseLineNumber = 0;
    unsigned long lineNumber = 0;

    bool tryToChangeSection(const QString& line);

    void parseInfoSection(std::map<QString, QString>& infoSectionValues, QString& line, QTextStream& stream);
    void parseAnswersSection(std::map<char, std::shared_ptr<Answer>>& answersMap, QString& line, QTextStream& stream);
};
}

#endif // PAGESPARSER_H
