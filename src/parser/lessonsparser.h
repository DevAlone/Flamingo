#ifndef LESSONSPARSER_H
#define LESSONSPARSER_H

#include "logger/parserlogger.h"
#include "models/lesson/lesson.h"
#include "parser.h"

#include <QObject>
#include <QtCore>

#include <memory>

namespace parser {
class LessonsParser : public Parser {
public:
    std::shared_ptr<Lesson> parseFile(const QString& path);

    enum class SECTION {
        NONE,
        INFO,
        PAGES
    };

private:
    SECTION section = SECTION::INFO;
    unsigned long lineNumber = 0;
    QString path;

    void parseInfoSection(std::shared_ptr<Lesson>& lesson, QString& line);
    void parsePagesSection(std::shared_ptr<Lesson>& lesson, QString& line, QTextStream& stream);

    // TODO: удалить эту функцию, оставить только tryToChangeSection
    bool isSection(const QString& line) const;
    bool tryToChangeSection(const QString& line);
};
}

#endif // LESSONSPARSER_H
