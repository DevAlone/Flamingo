#ifndef PAGESPARSER_H
#define PAGESPARSER_H

#include "parser.h"

#include "models/include.h"

namespace parser {
class PagesParser : public Parser {
public:
    PagesParser();

    /// function can return empty smart pointer.
    /// Check it before using.
    std::shared_ptr<Page> parsePage(QString& string,
        unsigned pageNumber,
        unsigned long baseLineNumber, const QString& path);

    enum class SECTION {
        NONE,
        INFO,
        ANSWERS
    };

private:
    SECTION section = SECTION::INFO;
    unsigned long baseLineNumber = 0;
    unsigned long lineNumber = 0;
    QString path;
    QString line;

    bool tryToChangeSection(const QString& line);

    // TODO: add vector
    void parseInfoSection(std::map<QString, QString>& infoSectionValues, QString& line, QTextStream& stream);

    void addAnswerToMap(std::map<QChar, std::shared_ptr<Answer>>& answersMap,
        QChar answerLetter,
        QString& answerBuffer);

    void parseAnswersSection(std::map<QChar, std::shared_ptr<Answer>>& answersMap, QString& line, QTextStream& stream);
};
}

#endif // PAGESPARSER_H
