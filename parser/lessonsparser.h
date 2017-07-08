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

    std::shared_ptr<Lesson> parseFile(const QString& path);

    void setLogger(std::shared_ptr<ParserLogger>& logger);

private:
    std::shared_ptr<ParserLogger> logger;
    template <typename T, typename... Args>
    void logEntry(Args... args)
    {
        if (logger)
            logger->addEntry(std::make_unique<T>(args...));
    }
};
}

#endif // LESSONSPARSER_H
