#ifndef COURSESPARSER_H
#define COURSESPARSER_H

#include "course.h"
#include "parserlogger.h"

#include <QObject>
#include <QVector>
#include <QtCore>

#include <vector>

namespace parser {
class CoursesParser : public QObject {
    Q_OBJECT
public:
    explicit CoursesParser(QObject* parent = nullptr);

    std::vector<Course> parseDirectory(const QString& path);
    void setLogger(std::shared_ptr<ParserLogger>& logger);

signals:

public slots:

private:
    Course parseCourse(const QString& courseDirPath);
    std::shared_ptr<ParserLogger> logger;
    template <typename T, typename... Args>
    void logEntry(Args... args)
    {
        if (logger)
            logger->addEntry(std::make_unique<T>(args...));
    }
};
}

#endif // COURSESPARSER_H
