#include "lessonsparser.h"
#include "logger/lessonsparserlogentry.h"
#include "pagesparser.h"
#include "parser.h"

#include <exceptions/lessonsparserexception.h>

#include <QChar>
#include <QtCore>

namespace parser {

std::shared_ptr<Lesson> LessonsParser::parseFile(const QString& path)
{
    this->path = path;
    logEntry<LessonsParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of lesson file was started"),
        path);

    std::shared_ptr<Lesson> lesson = std::make_shared<Lesson>(path); // TODO: ?

    QFile lessonFile(path);
    QString s;
    if (!lessonFile.exists()) {
        logEntry<LessonsParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("lesson file wasn't found here: ")
                + path,
            path);
        return lesson;
    }

    if (!lessonFile.open(QIODevice::ReadOnly)) {
        logEntry<LessonsParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("lesson file can't be opened. "
                        "Maybe you don't have permissions to do that"),
            path);
        return lesson;
    }

    {

        section = SECTION::INFO;

        QTextStream stream(&lessonFile);

        for (lineNumber = 0; !stream.atEnd(); lineNumber++) {
            QString line = stream.readLine();
            line = line.trimmed();

            // if line point to which section is started
            if (isSection(line)) {
                tryToChangeSection(line);
                continue;
            }

            switch (section) {
            case SECTION::INFO:
                parseInfoSection(lesson, line);
                break;
            case SECTION::PAGES:
                parsePagesSection(lesson, line, stream);
                break;
            }
        }
    }

    return lesson;
}

void LessonsParser::parseInfoSection(std::shared_ptr<Lesson>& lesson, QString& line)
{
    bool isOk;
    auto keyValue = getKeyValueFromString(line, &isOk, ':');
    auto& key = keyValue.first;
    auto& value = keyValue.second;

    if (!isOk) {
        logEntry<LessonsParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Unrecognized string. Expected ':', but is not found"),
            path,
            lineNumber,
            line,
            section);
        return;
    }

    if (key == "level") {
        int level = value.toInt(&isOk);
        if (!isOk || level < 1 || level > 10)
            logEntry<LessonsParserLogEntry>(
                LOG_ENTRY_TYPE::ERROR,
                QObject::tr("Invalid level of lesson value. It should be number from 1 to 10(including)"),
                path,
                lineNumber,
                line,
                section);
        if (lesson)
            lesson->setLevel(level);
    }
}

void LessonsParser::parsePagesSection(std::shared_ptr<Lesson>& lesson, QString& line, QTextStream& stream)
{
    logEntry<LessonsParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Start parsing of PAGES section"),
        path,
        lineNumber,
        line);

    unsigned pageNumber = 1;
    unsigned long pageLineNumber = 0;

    QString pageBuffer = "";

    bool isFirstLine = true;
    for (; !stream.atEnd(); lineNumber++) {
        if (isFirstLine)
            isFirstLine = false;
        else
            line = stream.readLine();

        QString trimmedLine = line.trimmed();

        if (isSection(line)) {
            if (tryToChangeSection(trimmedLine))
                break;
        }

        bool isOk;

        if (trimmedLine.startsWith("{") && trimmedLine.endsWith("}") && trimmedLine.size() > 2) {
            int number = trimmedLine.mid(1, trimmedLine.size() - 2).toInt(&isOk);
            if (isOk) {
                if (pageBuffer != "") {
                    PagesParser pagesParser;
                    pagesParser.setLogger(logger);

                    std::shared_ptr<Page> page = pagesParser.parsePage(
                        pageBuffer,
                        pageNumber,
                        pageLineNumber);

                    if (page)
                        lesson->addQuestion(page);

                    pageBuffer = "";
                }
                pageNumber = number;
                pageLineNumber = lineNumber;
                continue;
            }
        }

        pageBuffer += line;
    }

    if (pageBuffer != "") {
        PagesParser pagesParser;
        pagesParser.setLogger(logger);

        std::shared_ptr<Page> page = pagesParser.parsePage(
            pageBuffer,
            pageNumber,
            pageLineNumber);

        if (page)
            lesson->addQuestion(page);

        pageBuffer = "";
    }
}

bool LessonsParser::isSection(const QString& line) const
{
    return line.startsWith("[") && line.endsWith("]") && line.size() > 2;
}

bool LessonsParser::tryToChangeSection(const QString& line)
{
    QString substr = line.mid(1, line.size() - 2);
    substr = substr.toLower();

    if (substr == "questions")
        section = SECTION::PAGES;
    else if (substr == "info")
        section = SECTION::INFO;
    else
        return false;

    logEntry<LessonsParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Section was changed"),
        path,
        lineNumber,
        line,
        section);
    return true;
}
}
