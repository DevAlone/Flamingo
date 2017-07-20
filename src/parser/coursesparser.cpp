#include "coursesparser.h"
#include "logger/coursesparserlogentry.h"
#include "modulesparser.h"
#include "parser.h"

#include <QDebug>
#include <iostream>

namespace parser {

std::vector<Course> CoursesParser::parseDirectory(const QString& path)
{
    logEntry<CoursesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of courses directory was started"),
        path);

    std::vector<Course> courses;

    QDir baseDir(path);

    if (!baseDir.exists()) {
        logEntry<CoursesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Directory ") + path + QObject::tr(" doesn't exist"),
            baseDir.absolutePath());
        return courses;
    }

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
    logEntry<CoursesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of course was started"),
        courseDirPath);

    QDir courseDir(courseDirPath);

    Course course(courseDir.path()); // TODO: ?

    QString infoFilePath = courseDir.absoluteFilePath("info.txt");
    QFile infoFile(infoFilePath);

    if (!infoFile.exists()) {
        logEntry<CoursesParserLogEntry>(
            LOG_ENTRY_TYPE::WARNING,
            QObject::tr("info.txt file wasn't found here: ")
                + courseDir.absolutePath());
    } else if (!infoFile.open(QIODevice::ReadOnly)) {
        logEntry<CoursesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("info.txt can't be opened. Maybe you don't have permissions to do that"),
            courseDir.absolutePath());
    } else {
        logEntry<CoursesParserLogEntry>(
            LOG_ENTRY_TYPE::INFO,
            QObject::tr("Parsing of course info file was started"),
            infoFilePath);

        // parsing info file
        QTextStream stream(&infoFile);
        int lineNumber = 0;
        for (; !stream.atEnd(); lineNumber++) {

            QString line = stream.readLine();
            bool isOk;
            auto keyValue = getKeyValueFromString(line, &isOk, ':');

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
                if (!isOk || level < 1 || level > 10) {
                    logEntry<CoursesParserLogEntry>(
                        LOG_ENTRY_TYPE::ERROR,
                        QObject::tr("Unable to recognize level of course. It have to be number in range from 1 to 10"),
                        infoFilePath,
                        lineNumber,
                        line);
                    continue;
                }

                course.setLevel(level);
            }
        }
    }
    infoFile.close();

    // parsing modules
    ModulesParser modulesParser;
    modulesParser.setLogger(logger);

    auto modules = modulesParser.parseDirectory(courseDir.absoluteFilePath("modules"));
    course.addModules(modules);

    return course;
}
}
