#ifndef LESSONSPARSER_H
#define LESSONSPARSER_H

#include "lesson.h"
#include "logger/parserlogger.h"
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
        QUESTIONS
    };

private:
    SECTION section = SECTION::INFO;
    unsigned long lineNumber = 0;
    QString path;

    void parseInfoSection(std::shared_ptr<Lesson>& lesson, QString& line);
    void parseQuestionsSection(std::shared_ptr<Lesson>& lesson, QString& line, QTextStream& stream);

    // TODO: удалить эту функцию, оставить только tryToChangeSection
    bool isSection(const QString& line) const;
    bool tryToChangeSection(const QString& line);
};
}

#endif // LESSONSPARSER_H
