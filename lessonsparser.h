#ifndef LESSONSPARSER_H
#define LESSONSPARSER_H

#include "lesson.h"

#include <QObject>
#include <QtCore>

class LessonsParser {
public:
    LessonsParser();

    static Lesson parseFile(const QString& path);
};

#endif // LESSONSPARSER_H
