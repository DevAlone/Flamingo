#include "lessonsparser.h"
#include "lessonsparserlogentry.h"
#include "parser.h"

#include <exceptions/lessonsparserexception.h>

#include <QChar>
#include <QtCore>

namespace parser {
LessonsParser::LessonsParser()
{
}

void LessonsParser::setLogger(std::shared_ptr<ParserLogger>& logger)
{
    this->logger = logger;
}

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

    // TODO: remove all fucking exceptions

    // TODO: parse
    {

        section = SECTION::DESCRIPTION;

        //        std::shared_ptr<Question> question;

        QTextStream stream(&lessonFile);
        lineNumber = 0;

        for (; !stream.atEnd(); lineNumber++) {
            QString line = stream.readLine();
            line = line.trimmed();

            // if line point to which section is started
            if (isSection(line)) {
                tryToChangeSection(line);

                //                if (question) {
                //                    logEntry<LessonsParserLogEntry>(
                //                        LOG_ENTRY_TYPE::DEBUG,
                //                        QObject::tr("Adding question"),
                //                        path,
                //                        lineNumber,
                //                        section);
                //                    lesson->addQuestion(question);
                //                    question.reset();
                //                }
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

        //        if (question) {
        //            logEntry<LessonsParserLogEntry>(
        //                LOG_ENTRY_TYPE::DEBUG,
        //                QObject::tr("Adding question"),
        //                path,
        //                lineNumber,
        //                section);
        //            lesson->addQuestion(question);
        //            question.reset();
        //        }
    }

    //lesson->addQuestion(Question());

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

    int questionNumber = 1;
    QString questionBuffer = "";

    bool isFirstLine = true;
    for (; !stream.atEnd(); lineNumber++) {
        if (isFirstLine)
            isFirstLine = false;
        else
            line = stream.readLine();
        // TODO: line = line.trimmed();

        if (isSection(line)) {
            if (tryToChangeSection(line))
                break;
        }

        bool isOk;
        auto keyValue = getKeyValueFromString(line, &isOk, ':');
        auto& key = keyValue.first;
        // auto& value = keyValue.second;

        if (isOk) {
            int number = key.toInt(&isOk);
            if (isOk) {
                if (questionBuffer != "") {
                    logEntry<LessonsParserLogEntry>(
                        LOG_ENTRY_TYPE::DEBUG,
                        QObject::tr("Start parsing of question number ")
                            + QString::number(questionNumber)
                            + QObject::tr(" from buffer"),
                        path);
                    // TODO: parse and create question and push to lesson

                    questionBuffer
                        = "";
                }
                questionNumber = number;
                continue;
            }
        }

        questionBuffer += line;
    }

    if (questionBuffer != "") {
        // TODO: parse and create question and push to lesson
        logEntry<LessonsParserLogEntry>(
            LOG_ENTRY_TYPE::DEBUG,
            QObject::tr("Start parsing of question number ")
                + QString::number(questionNumber)
                + QObject::tr(" from buffer"),
            path);
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
