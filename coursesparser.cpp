#include "coursesparser.h"
#include "exceptions/coursesparserexception.h"
#include "exceptions/parseerrorexception.h"
#include "modulesparser.h"
#include "parser.h"

#include <QDebug>
#include <iostream>

CoursesParser::CoursesParser(QObject* parent)
    : QObject(parent)
{
}

std::vector<Course> CoursesParser::parseDirectory(const QString& path)
{
    std::vector<Course> courses;

    QDir baseDir(path);

    if (!baseDir.exists())
        throw CoursesParserException(tr("Directory ") + path + tr(" doesn't exist"));

    auto entries = baseDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    for (auto& entry : entries) {
        //Course course(entry); // TODO: убедиться, что entry не будет абсолютным путём

        QString courseDirPath = baseDir.absoluteFilePath(entry);

        QFileInfo fileInfo(courseDirPath);

        if (!fileInfo.isDir())
            continue;

        Course course = parseCourse(courseDirPath);

        courses.push_back(course);
    }

    return courses;
}

Course CoursesParser::parseCourse(const QString& courseDirPath)
{
    QDir courseDir(courseDirPath);

    Course course(courseDir.path()); // TODO: ?

    QString infoFilePath = courseDir.absoluteFilePath("info.txt");
    QFile infoFile(infoFilePath);

    if (!infoFile.exists())
        throw CoursesParserException(
            QString(tr("info.txt file wasn't found here: "))
            + courseDir.absolutePath());

    if (!infoFile.open(QIODevice::ReadOnly))
        throw CoursesParserException(
            QString(tr("info.txt can't be opened: "))
            + courseDir.absolutePath() + tr(". Maybe you don't have permissions to do that"));

    // parsing info file
    {
        QTextStream stream(&infoFile);
        int stringNumber = 0;
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            bool isOk;
            auto keyValue = Parser::getKeyValueFromString(line, &isOk, ':');

            if (!isOk)
                continue;

            auto& key = keyValue.first;
            auto& value = keyValue.second;

            // TODO: check for empty strings

            std::cout << "key = " << key.toStdString() << "; value = " << value.toStdString() << "; " << std::endl;

            if (key == "author") {
                course.setAuthor(value);
            } else if (key == "level") {
                bool isOk;
                int level = value.toInt(&isOk);
                if (!isOk || level < 1 || level > 10)
                    throw ParseErrorException(
                        "Unable to recognize level of course. It have to be number in range from 1 to 10",
                        stringNumber);

                course.setLevel(level);
            }

            stringNumber++;
        }
    }
    infoFile.close();

    // parsing modules
    ModulesParser modulesParser;
    auto modules = modulesParser.parseDirectory(courseDir.absoluteFilePath("modules"));
    course.addModules(modules);

    return course;
}
