#include "pagesparser.h"
#include "logger/pagesparserlogentry.h"

#include <answer.h>

namespace parser {
PagesParser::PagesParser()
{
}

std::shared_ptr<Page> PagesParser::parsePage(const QString& string, unsigned questionNumber, unsigned long baseLineNumber)
{

    // TODO: parse Question

    std::shared_ptr<Question> question = std::make_shared<Question>();

    //    std::map<QString, QString> map;

    QTextStream stream(string);

    this->baseLineNumber = baseLineNumber;
    lineNumber = 0;

    std::map<QString, QString> infoSectionMap;
    std::map<char, std::shared_ptr<Answer>> answersMap;

    for (; !stream.atEnd(); lineNumber++) {
        QString line = stream.readLine();
        QString trimmedLine = line.trimmed();

        // if line poing to start of section
        if (tryToChangeSection(trimmedLine))
            continue;

        // TODO: do it
        switch (section) {
        case SECTION::INFO:
            parseInfoSection(infoSectionMap, line, stream);
            break;
        case SECTION::ANSWERS:
            parseAnswersSection(arguments);
            break;
        default:
            break;
        }
    }

    // TODO: create question from infoSectionMap and questions
    // TODO: use fabric method

    return std::shared_ptr<Question>();
}

bool PagesParser::tryToChangeSection(const QString& line)
{
    // TODO: make trimmed

    // if it isn't section
    if (!(line.startsWith("/") && line.endsWith("/") && line.size() > 2))
        return false;

    QString substr = line.mid(1, line.size() - 2);

    substr = substr.toLower();

    if (substr == "info") {
        section = SECTION::INFO;
    } else if (substr == "answers") {
        section = SECTION::ANSWERS;
    } else
        return false;

    logEntry<PagesParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Section was changed"),
        path,
        baseLineNumber + lineNumber,
        line,
        section);
    return true;
}

void PagesParser::parseInfoSection(std::map<QString, QString>& infoSectionValues, QString& line, QTextStream& stream)
{
    logEntry<PagesParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Start parsing of INFO section"),
        path,
        baseLineNumber + lineNumber,
        line);

    bool isFirstLine = true;

    std::pair<QString, QString> infoSectionBuffer;

    for (; !stream.atEnd(); lineNumber++) {
        if (isFirstLine)
            isFirstLine = false;
        else
            line = stream.readLine();

        QString trimmedLine = line.trimmed();

        if (tryToChangeSection(trimmedLine))
            break;

        bool isOk;
        auto keyValue = getKeyValueFromString(line, &isOk, ":");
        auto& key = keyValue.first;
        auto& value = keyValue.second;

        if (isOk) {
            if (infoSectionBuffer.first != "") {
                auto it = infoSectionValues.find(key);
                if (it != map.end()) {
                    logEntry<PagesParserLogEntry>(
                        LOG_ENTRY_TYPE::ERROR,
                        QObject::tr("Adding more than one value with same key"),
                        path,
                        baseLineNumber + lineNumber,
                        line);
                    *it = infoSectionBuffer.second;
                } else {
                    infoSectionValues.insert(infoSectionBuffer);
                }
            }
            infoSectionBuffer = std::make_pair<QString, QString>("", "");
        } else {
            infoSectionBuffer.second += " " + trimmedLine;
        }
    }
    // check buffer
    if (infoSectionBuffer.first != "") {
        auto it = infoSectionValues.find(key);
        if (it != map.end()) {
            logEntry<PagesParserLogEntry>(
                LOG_ENTRY_TYPE::ERROR,
                QObject::tr("Adding more than one value with same key"),
                path,
                baseLineNumber + lineNumber,
                line);
            *it = infoSectionBuffer.second;
        } else {
            infoSectionValues.insert(infoSectionBuffer);
        }
    }
    infoSectionBuffer = std::make_pair<QString, QString>("", "");
}

void PagesParser::parseAnswersSection(std::map<char, std::shared_ptr<Answer>>& answersMap, QString& line, QTextStream& stream)
{
    throw std::logic_error("not implemented");

    logEntry<PagesParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Start parsing of ANSWERS section"),
        path,
        baseLineNumber + lineNumber,
        line);

    bool isFirstLine = true;

    QString answerBuffer = "";
    for (; !stream.atEnd(); lineNumber++) {
        if (isFirstLine)
            isFirstLine = false;
        else
            line = stream.readLine();

        QString trimmedLine = line.trimmed();

        if (tryToChangeSection(trimmedLine))
            break;

        // TODO: find {a-z} by regex and call answer parser
        // buffer += line + "\n";
    }

    // TODO: call answers parser
}
}
