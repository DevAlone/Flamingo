#include "pagesparser.h"
#include "answersparser.h"
#include "logger/pagesparserlogentry.h"

#include "models/include.h"

#include "exceptions/pagecreatingerror.h"

namespace parser {
PagesParser::PagesParser()
{
}

std::shared_ptr<Page> PagesParser::parsePage(QString& string,
    unsigned pageNumber,
    unsigned long baseLineNumber,
    const QString& path)
{
    this->path = path;
    std::shared_ptr<Page> page; // = std::make_shared<Page>();

    //    std::map<QString, QString> map;

    QTextStream stream(&string);

    this->baseLineNumber = baseLineNumber;
    lineNumber = 0;

    std::map<QString, QString> infoSectionMap;
    std::map<QChar, std::shared_ptr<Answer>> answersMap;

    for (; !stream.atEnd(); lineNumber++) {
        line = stream.readLine();
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
            parseAnswersSection(answersMap, line, stream);
            break;
        default:
            break;
        }
    }

    // TODO: create question from infoSectionMap and questions
    // TODO: use fabric method

    try {
        page = Page::createPage(pageNumber, infoSectionMap, answersMap);
        if (!page) {
            // TODO: do something
            return std::shared_ptr<Page>();
        }
    } catch (const PageCreatingError& exception) {
        logEntry<PagesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Creating page error: ") + exception.getMessage(),
            path,
            baseLineNumber);
        return std::shared_ptr<Page>();
    } catch (...) {
        logEntry<PagesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Something wrong happened"),
            path,
            baseLineNumber);
        throw std::exception();
    }

    return page;
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

    std::pair<QString, QString> infoSectionBuffer = std::make_pair("", "");

    std::pair<QString, QString> keyValue;
    // TODO: add check for empty stream but non empty line
    for (; !stream.atEnd(); lineNumber++) {
        if (isFirstLine)
            isFirstLine = false;
        else
            line = stream.readLine();

        QString trimmedLine = line.trimmed();

        if (tryToChangeSection(trimmedLine))
            break;

        bool isOk;
        keyValue = getKeyValueFromString(trimmedLine, &isOk, ':');
        auto& key = keyValue.first;
        // auto& value = keyValue.second;

        if (isOk) {
            if (!infoSectionBuffer.first.isEmpty()) {
                auto it = infoSectionValues.find(key);
                if (it != infoSectionValues.end()) {
                    logEntry<PagesParserLogEntry>(
                        LOG_ENTRY_TYPE::ERROR,
                        QObject::tr("Adding more than one value with same key"),
                        path,
                        baseLineNumber + lineNumber,
                        line);
                    it->second = infoSectionBuffer.second;
                } else {
                    infoSectionValues.insert(infoSectionBuffer);
                }
            }
            infoSectionBuffer = keyValue;
        } else {
            infoSectionBuffer.second += " " + trimmedLine;
        }
    }
    // check buffer
    if (infoSectionBuffer.first != "") {
        auto& key = keyValue.first;
        auto it = infoSectionValues.find(key);
        if (it != infoSectionValues.end()) {
            logEntry<PagesParserLogEntry>(
                LOG_ENTRY_TYPE::ERROR,
                QObject::tr("Adding more than one value with same key"),
                path,
                baseLineNumber + lineNumber,
                line);
            it->second = infoSectionBuffer.second;
        } else {
            infoSectionValues.insert(infoSectionBuffer);
        }
    }
    infoSectionBuffer = std::make_pair<QString, QString>("", "");
}

void PagesParser::addAnswerToMap(std::map<QChar, std::shared_ptr<Answer>>& answersMap,
    QChar answerLetter,
    QString& answerBuffer)
{
    if (answerBuffer.isEmpty())
        return;

    auto it = answersMap.find(answerLetter);
    if (it != answersMap.end()) {
        logEntry<PagesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Answer with letter '") + answerLetter + QObject::tr("already exist"),
            path,
            baseLineNumber + lineNumber,
            line,
            section);
        return;
    }

    AnswersParser parser;
    parser.setLogger(logger);

    auto answer = parser.parseAnswer(answerBuffer, answerLetter, baseLineNumber + lineNumber, path);
    if (!answer) {
        // TODO: log this shit
        return;
    }
    answersMap.insert(std::make_pair(answerLetter, answer));
}

void PagesParser::parseAnswersSection(std::map<QChar, std::shared_ptr<Answer>>& answersMap, QString& line, QTextStream& stream)
{
    logEntry<PagesParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Start parsing of ANSWERS section"),
        path,
        baseLineNumber + lineNumber,
        line);

    bool isFirstLine = true;

    QChar answerLetter = 'a';
    QString answerBuffer = "";

    for (; !stream.atEnd(); lineNumber++) {
        if (isFirstLine)
            isFirstLine = false;
        else
            line = stream.readLine();

        QString trimmedLine = line.trimmed();

        if (tryToChangeSection(trimmedLine))
            break;

        bool newAnswerFound = false;
        if (trimmedLine.length() > 2) {
            QString answerSubstr = trimmedLine.left(3).toLower();
            if (answerSubstr.startsWith('{') && answerSubstr.endsWith('}')) {
                QChar letter = answerSubstr[1];
                if (letter >= 'a' && letter <= 'z') {
                    addAnswerToMap(answersMap, answerLetter, answerBuffer);

                    newAnswerFound = true;
                    answerLetter = letter;
                    if (trimmedLine > 3)
                        answerBuffer = trimmedLine.mid(3) + "\n";
                    else
                        answerBuffer = "";
                }
            }
        }
        if (!newAnswerFound)
            answerBuffer += trimmedLine + "\n";
    }

    addAnswerToMap(answersMap, answerLetter, answerBuffer);
}
}
