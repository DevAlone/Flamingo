// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "infosectionparser.h"
#include "logger/lessonsparserlogentry.h"
#include "pagesparser.h"
#include "parser.h"

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

    QFileInfo lessonFileInfo(lessonFile.fileName());

    lesson->setName(lessonFileInfo.fileName()); // TODO: ?

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
                parseInfoSection(lesson, line, stream);
                break;
            case SECTION::PAGES:
                parsePagesSection(lesson, line, stream);
                break;
            }
        }
    }

    return lesson;
}

void LessonsParser::parseInfoSection(std::shared_ptr<Lesson>& lesson, QString& line, QTextStream& stream)
{
    logEntry<LessonsParserLogEntry>(
        LOG_ENTRY_TYPE::DEBUG,
        QObject::tr("Start parsing of INFO section"),
        path,
        lineNumber,
        line);

    QString buffer = "";

    bool isFirstLine = true;
    for (; !stream.atEnd(); lineNumber++) {
        if (isFirstLine)
            isFirstLine = false;
        else
            line = stream.readLine();
        QString trimmedLine = line.trimmed();

        if (tryToChangeSection(trimmedLine))
            break;

        buffer += line;
    }

    InfoSectionParser infoSectionParser;
    infoSectionParser.setLogger(logger);

    std::map<QString, QString> infoSectionData
        = infoSectionParser.parseInfoSection(buffer);

    for (auto& keyValue : infoSectionData) {
        auto& key = keyValue.first;
        auto& value = keyValue.second;

        if (key == "name") {
            lesson->setName(value);
        } else if (key == "description") {
            lesson->setDescription(value);
        }
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

        if (trimmedLine.isEmpty())
            continue;

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
                        pageLineNumber,
                        path);

                    if (page)
                        lesson->addPage(page);

                    pageBuffer = "";
                }
                pageNumber = number;
                pageLineNumber = lineNumber;
                continue;
            }
        }

        pageBuffer += line + "\n";
    }

    if (pageBuffer != "") {
        PagesParser pagesParser;
        pagesParser.setLogger(logger);

        std::shared_ptr<Page> page = pagesParser.parsePage(
            pageBuffer,
            pageNumber,
            pageLineNumber,
            path);

        if (page)
            lesson->addPage(page);

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

    if (substr == "pages")
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
