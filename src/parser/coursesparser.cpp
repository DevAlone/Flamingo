#include "coursesparser.h"
#include "infosectionparser.h"
#include "logger/coursesparserlogentry.h"
#include "modulesparser.h"
#include "parser.h"

#include <QDebug>

namespace parser {

std::vector<std::shared_ptr<Course>> CoursesParser::parseCoursesInDirectory(const QString& path)
{
    logEntry<CoursesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of courses directory was started"),
        path);

    std::vector<std::shared_ptr<Course>> courses;

    std::vector<QString> coursesList = listCoursesInDirectory(path);

    for (auto& courseName : coursesList) {
        QDir courseDir(path);
        auto course = parseCourse(courseDir.absoluteFilePath(courseName));

        courses.push_back(course);
    }

    return courses;
}

std::vector<QString> CoursesParser::listCoursesInDirectory(const QString& path)
{
    logEntry<CoursesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("List of courses in directory was started"),
        path);

    std::vector<QString> courses;

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
        QString courseDirPath = baseDir.absoluteFilePath(entry);

        QFileInfo fileInfo(courseDirPath);

        if (!fileInfo.isDir())
            continue;

        courses.push_back(QDir(courseDirPath).dirName());
    }

    return courses;
}

std::shared_ptr<Course> CoursesParser::parseCourse(const QString& courseDirPath)
{
    logEntry<CoursesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of course was started"),
        courseDirPath);

    QDir courseDir(courseDirPath);

    std::shared_ptr<Course> coursePtr = std::make_shared<Course>(courseDir.dirName());

    Course& course = *coursePtr;

    QString infoFilePath = courseDir.absoluteFilePath("info.txt");

    InfoSectionParser infoFileParser;
    infoFileParser.setLogger(logger);

    auto infoFileMap = infoFileParser.parseInfoFile(infoFilePath);

    for (auto& keyValue : infoFileMap) {
        auto& key = keyValue.first;
        auto& value = keyValue.second;

        if (key == "author") {
            course.setAuthor(value);
        } else if (key == "level") {
            bool isOk;
            int level = value.toInt(&isOk);
            if (!isOk || level < 1 || level > 10) {
                logEntry<CoursesParserLogEntry>(
                    LOG_ENTRY_TYPE::ERROR,
                    QObject::tr("Unable to recognize level of course. It have to be number in range from 1 to 10"),
                    infoFilePath);
                continue;
            }

            course.setLevel(level);
        } else if (key == "name") {
            course.setName(value);
        } else if (key == "description") {
            course.setDescription(value);
        } else if (key == "language") {
            course.setLanguageCode(value);
        }
    }

    // parsing modules
    ModulesParser modulesParser;
    modulesParser.setLogger(logger);

    auto modules = modulesParser.parseDirectory(courseDir.absoluteFilePath("modules"));
    course.addModules(modules);

    return coursePtr;
}
}
