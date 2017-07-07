#include "lessonsparser.h"

#include <exceptions/lessonsparserexception.h>

LessonsParser::LessonsParser()
{
}

std::shared_ptr<Lesson> LessonsParser::parseFile(const QString& path)
{
    std::shared_ptr<Lesson> lesson = std::make_shared<Lesson>(path); // TODO: ?

    QFile lessonFile(path);
    QString s;
    if (!lessonFile.exists())
        throw LessonsParserException(
            QObject::tr("lesson file wasn't found here: ")
            + path);

    if (!lessonFile.open(QIODevice::ReadOnly))
        throw LessonsParserException(
            QObject::tr("lesson file can't be opened: ")
            + path
            + QObject::tr(". Maybe you don't have permissions to do that"));

    // TODO: parse
    lesson->addQuestion(Question());

    return lesson;
}
