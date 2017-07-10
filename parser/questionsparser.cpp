#include "questionsparser.h"
#include "logger/questionsparserlogentry.h"

namespace parser {
QuestionsParser::QuestionsParser()
{
}

std::shared_ptr<Question> QuestionsParser::parseString(const QString& string, unsigned questionNumber, unsigned long baseLineNumber)
{

    // TODO: parse Question

    std::shared_ptr<Question> question = std::make_shared<Question>();

    //    std::map<QString, QString> map;

    QTextStream stream(string);

    this->baseLineNumber = baseLineNumber;
    lineNumber = 0;
    //    std::pair<QString, QString> buffer;

    for (; !stream.atEnd(); lineNumber++) {
        QString line = stream.readLine();
        QString trimmedLine = line.trimmed();

        // if line poing to start of section
        if (tryToChangeSection(trimmedLine))
            continue;

        // TODO: do it
        switch (section) {
        case SECTION::INFO:
            parseInfoSection(arguments);
            break;
        case SECTION::ANSWERS:
            parseAnswersSection(arguments);
            break;
        default:
            break;
        }

        //        bool isOk;
        //        auto keyValue = getKeyValueFromString(string, &isOk, ":");
        //        auto& key = keyValue.first;
        //        auto& value = keyValue.second;

        //        if (isOk) {
        //            // flush buffer
        //            if (buffer.first != "") {
        //                auto it = map.find(key);
        //                if (it == map.end()) {
        //                    logEntry<QuestionsParserLogEntry>(
        //                        LOG_ENTRY_TYPE::ERROR,
        //                        QObject::tr("Adding more than one value with same key"),
        //                        path,
        //                        baseLineNumber + lineNumber,
        //                        line);
        //                    *it = buffer.second;
        //                } else {
        //                    map.insert(buffer);
        //                }
        //            }
        //        } else {
        //            buffer.second += " " + line;
        //        }
    }

    return std::shared_ptr<Question>();
}

bool QuestionsParser::tryToChangeSection(const QString& line)
{
    // if it isn't section
    if (!(line.startsWith("[") && line.endsWith("]") && line.size() > 2))
        return false;

    QString substr = line.mid(1, line.size() - 2);

    substr = substr.toLower();

    if (substr == "info") {
        section = SECTION::INFO;
    } else if (substr == "answers") {
        section = SECTION::ANSWERS;
    } else
        return false;

    logEntry<QuestionsParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Section was changed"),
        path,
        baseLineNumber + lineNumber,
        line,
        section);
    return true;
}
}
