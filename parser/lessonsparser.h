#ifndef LESSONSPARSER_H
#define LESSONSPARSER_H

#include "lesson.h"
#include "parserlogger.h"

#include <QObject>
#include <QtCore>

#include <memory>

namespace parser {
class LessonsParser {
public:
    LessonsParser();
    void setLogger(std::shared_ptr<ParserLogger>& logger);

    std::shared_ptr<Lesson> parseFile(const QString& path);

    enum class SECTION {
        NONE,
        DESCRIPTION,
        QUESTIONS
    };

private:
    std::shared_ptr<ParserLogger> logger;
    template <typename T, typename... Args>
    void logEntry(Args... args)
    {
        if (logger)
            logger->addEntry(std::make_unique<T>(args...));
    }

    SECTION section = SECTION::DESCRIPTION;
    unsigned long lineNumber = 0;
    QString path;

    void parseDescriptionSection(std::shared_ptr<Lesson>& lesson, QString& line);
    void parseQuestionsSection(std::shared_ptr<Lesson>& lesson, QString& line, QTextStream& stream);

    bool isSection(const QString& line) const;
    bool tryToChangeSection(const QString& line);
};
}

#endif // LESSONSPARSER_H
