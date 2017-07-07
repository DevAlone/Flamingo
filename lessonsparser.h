#ifndef LESSONSPARSER_H
#define LESSONSPARSER_H

#include "lesson.h"

#include <QObject>
#include <QtCore>

#include <memory>

class LessonsParser {
public:
    LessonsParser();

    static std::shared_ptr<Lesson> parseFile(const QString& path);

private:
};

#endif // LESSONSPARSER_H
