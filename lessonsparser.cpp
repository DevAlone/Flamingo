#include "lessonsparser.h"
#include "parser.h"

#include <exceptions/lessonsparserexception.h>

#include <QChar>
#include <QtCore>

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
    {
        enum class STATE {
            DESCRIPTION,
            QUESTIONS
        };

        STATE state = STATE::DESCRIPTION;
        std::shared_ptr<Question> question;

        QTextStream stream(&lessonFile);
        int stringNumber = 0;

        qDebug() << "parsing of lesson was started";
        while (!stream.atEnd()) {
            QString line = stream.readLine();

            line = line.trimmed();

            if (line.startsWith("[") && line.endsWith("]") && line.size() > 2) {
                QString substr = line.mid(1, line.size() - 2);
                substr = substr.toLower();

                if (substr == "questions") {
                    state = STATE::QUESTIONS;
                    qDebug() << "state changed to [Questions]";
                }

                if (question) {
                    qDebug() << "adding question...";
                    lesson->addQuestion(question);
                    question.reset();
                }
                continue;
            }

            bool isOk;
            auto keyValue = Parser::getKeyValueFromString(line, &isOk, ':');

            auto& key = keyValue.first;
            auto& value = keyValue.second;

            switch (state) {
            case STATE::DESCRIPTION:
                if (!isOk)
                    throw LessonsParserException(
                        QObject::tr("Error during parsing [Description] section "
                                    "Unrecognized string. Expected ':', but is not found in here: ")
                        + line);

                if (key == "level") {
                    qDebug() << "level of lesson is " << value;
                    int level = value.toInt(&isOk);
                    if (!isOk || level < 1 || level > 10)
                        throw LessonsParserException(
                            QObject::tr("Error during parsing [Description] section "
                                        "Invalid level value. It should be number from 1 to 10, but '")
                            + value
                            + QObject::tr("' is found"));
                    lesson->setLevel(level);
                }
                break;
            case STATE::QUESTIONS:
                if (!isOk) {
                    keyValue = Parser::getKeyValueFromString(line, &isOk, '-');
                    if (isOk) {
                        // TODO: parse answers
                        qDebug() << "answer: key = " << key << "; value = " << value;
                    } else {
                        int questionNumber = line.simplified().toInt(&isOk);
                        qDebug() << "question number is " << line;
                        if (!isOk)
                            throw LessonsParserException(
                                QObject::tr("Error during parsing [Questions] section. "
                                            "Unrecognized string: ")
                                + line);

                        if (question) {
                            qDebug() << "adding question...";
                            lesson->addQuestion(question);
                            question.reset();
                        }
                        question = std::make_shared<Question>(questionNumber);
                        qDebug() << "creating new question number " << questionNumber;
                    }
                    continue;
                }

                // TODO: parse question properties
                qDebug() << "property: key = " << key << "; value = " << value;

                break;
            }

            stringNumber++;
        }

        if (question) {
            qDebug() << "adding question...";
            lesson->addQuestion(question);
            question.reset();
        }
    }

    //lesson->addQuestion(Question());

    return lesson;
}
