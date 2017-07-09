#include "lessonsparser.h"
#include "logger/lessonsparserlogentry.h"
#include "parser.h"
#include "questionsparser.h"

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

        section = SECTION::DESCRIPTION;

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
            case SECTION::DESCRIPTION:
                parseDescriptionSection(lesson, line);
                break;
            case SECTION::QUESTIONS:
                parseQuestionsSection(lesson, line, stream);
                break;
            }
        }
    }

    return lesson;
}

void LessonsParser::parseDescriptionSection(std::shared_ptr<Lesson>& lesson, QString& line)
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

void LessonsParser::parseQuestionsSection(std::shared_ptr<Lesson>& lesson, QString& line, QTextStream& stream)
{
    logEntry<LessonsParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Start paring of QUESTIONS section"),
        path,
        lineNumber,
        line);

    qDebug() << path;

    unsigned questionNumber = 1;
    unsigned long questionLineNumber = 0;

    QString questionBuffer = "";

    bool isFirstLine = true;
    for (; !stream.atEnd(); lineNumber++) {
        if (isFirstLine)
            isFirstLine = false;
        else
            line = stream.readLine();

        line = line.trimmed();

        if (isSection(line)) {
            if (tryToChangeSection(line))
                break;
        }

        bool isOk;
        auto keyValue = getKeyValueFromString(line, &isOk, ':');
        auto& key = keyValue.first;

        if (isOk) {
            int number = key.toInt(&isOk);
            if (isOk) {
                if (questionBuffer != "") {
                    QuestionsParser questionsParser;
                    questionsParser.setLogger(logger);

                    std::shared_ptr<Question> question = questionsParser.parseString(
                        questionBuffer,
                        questionNumber,
                        questionLineNumber);

                    if (question)
                        lesson->addQuestion(question);

                    questionBuffer = "";
                }
                questionNumber = number;
                questionLineNumber = lineNumber;
                continue;
            }
        }

        questionBuffer += line;
    }

    if (questionBuffer != "") {
        QuestionsParser questionsParser;
        questionsParser.setLogger(logger);

        std::shared_ptr<Question> question = questionsParser.parseString(
            questionBuffer,
            questionNumber,
            questionLineNumber);

        if (question)
            lesson->addQuestion(question);

        questionBuffer = "";
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
        section = SECTION::QUESTIONS;
    else if (substr == "description")
        section = SECTION::DESCRIPTION;
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
