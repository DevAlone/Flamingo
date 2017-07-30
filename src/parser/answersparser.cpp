#include "answersparser.h"

#include <parser/logger/answersparserlogentry.h>

#include <exceptions/answercreatingerror.h>

namespace parser {
AnswersParser::AnswersParser()
{
}

std::shared_ptr<Answer> AnswersParser::parseAnswer(QString& string, QChar answerLetter, unsigned long baseLineNumber, QString path)
{
    this->path = path;
    this->baseLineNumber = baseLineNumber;
    lineNumber = 0;

    QTextStream stream(&string);

    std::map<QString, QString> keyValueMap;
    std::vector<std::pair<QString, QString>> keyValueVec;

    std::pair<QString, QString> buffer = std::make_pair("content", "");

    for (; !stream.atEnd(); lineNumber++) {
        line = stream.readLine();
        QString trimmedLine = line.trimmed();

        bool isOk;
        auto keyValue = parser::getKeyValueFromString(trimmedLine, &isOk, ':');
        auto& key = keyValue.first;
        auto& value = keyValue.second;

        if (isOk) {
            insertKeyValue(keyValueMap, keyValueVec, buffer);
            buffer = keyValue;
        } else
            buffer.second += " " + trimmedLine + "\n";
    }
    insertKeyValue(keyValueMap, keyValueVec, buffer);

    std::shared_ptr<Answer> answer;

    try {
        answer = Answer::createAnswer(keyValueMap, keyValueVec);
        if (!answer) {
            // TODO: log this shit
            return std::shared_ptr<Answer>();
        }
    } catch (const AnswerCreatingError& exception) {
        // TODO: log this shit
        return std::shared_ptr<Answer>();
    }
    return answer;
}

void AnswersParser::insertKeyValue(std::map<QString, QString>& keyValueMap,
    std::vector<std::pair<QString, QString>>& keyValueVec,
    std::pair<QString, QString> buffer)
{
    // check buffer
    if (buffer.first.isEmpty()) {
        logEntry<AnswersParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Unable to recognize this shit: ") + line,
            path,
            baseLineNumber + lineNumber,
            line);
        return;
    }
    auto it = keyValueMap.find(buffer.first);
    if (it != keyValueMap.end()) {
        // TODO: remove this
        logEntry<AnswersParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Adding more than one key"),
            path,
            baseLineNumber + lineNumber,
            line);
        it->second = buffer.second;
    } else {
        keyValueMap.insert(buffer);
    }
    keyValueVec.push_back(buffer);
}
}
