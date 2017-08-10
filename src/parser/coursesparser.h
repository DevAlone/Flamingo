#ifndef COURSESPARSER_H
#define COURSESPARSER_H

#include "logger/parserlogger.h"
#include "models/course.h"
#include "parser.h"

#include <QObject>
#include <QVector>
#include <QtCore>

#include <vector>

namespace parser {
class CoursesParser : public Parser {
public:
    std::vector<std::shared_ptr<Course> > parseCoursesInDirectory(const QString& path);

    std::vector<QString> listCoursesInDirectory(const QString& path);

    std::shared_ptr<Course> parseCourse(const QString& courseDirPath);

private:
};
}

#endif // COURSESPARSER_H
