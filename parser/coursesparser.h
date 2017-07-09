#ifndef COURSESPARSER_H
#define COURSESPARSER_H

#include "course.h"
#include "logger/parserlogger.h"
#include "parser.h"

#include <QObject>
#include <QVector>
#include <QtCore>

#include <vector>

namespace parser {
class CoursesParser : public Parser {
public:
    std::vector<Course> parseDirectory(const QString& path);

private:
    Course parseCourse(const QString& courseDirPath);
};
}

#endif // COURSESPARSER_H
