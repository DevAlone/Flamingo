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



#include <parser/logger/infosectionparserlogentry.h>

namespace parser {
std::map<QString, QString> InfoSectionParser::parseInfoFile(const QString& path)
{
    QFile infoFile(path);

    std::map<QString, QString> result;
    if (!infoFile.exists()) {
        logEntry<InfoSectionParserLogEntry>(
            LOG_ENTRY_TYPE::WARNING,
            QObject::tr("info.txt file wasn't found here: ")
                + path);
    } else if (!infoFile.open(QIODevice::ReadOnly)) {
        logEntry<InfoSectionParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("info.txt can't be opened. "
                        "Maybe you don't have permissions to do that"),
            path);

    } else {
        logEntry<InfoSectionParserLogEntry>(
            LOG_ENTRY_TYPE::INFO,
            QObject::tr("Parsing of info file was started"),
            path);

        QTextStream stream(&infoFile);
        QString data = stream.readAll();
        result = parseInfoSection(data, path);

        infoFile.close();
    }
    return result;
}
std::map<QString, QString> InfoSectionParser::parseInfoSection(
    QString& data,
    const QString& path,
    std::vector<std::pair<QString, QString>>* keyValueVector)
{
    std::map<QString, QString> result;

    std::pair<QString, QString> buffer
        = std::make_pair<QString, QString>("", "");

    QTextStream stream(&data);
    int lineNumber = 0;
    for (; !stream.atEnd(); lineNumber++) {
        QString line = stream.readLine();
        bool isOk;
        auto keyValue = getKeyValueFromString(line, &isOk, ':');

        if (!isOk) {
            buffer.second += "\n" + line;
            continue;
        }

        auto& key = keyValue.first;
        auto& value = keyValue.second;

        if (!key.isEmpty()) {
            if (result.find(key) != result.end()) {
                logEntry<InfoSectionParserLogEntry>(
                    LOG_ENTRY_TYPE::WARNING,
                    QObject::tr("Attempting to add more than one value with the same key"),
                    path,
                    lineNumber);
            } else {
                result.insert(buffer);
            }
            if (keyValueVector)
                keyValueVector->push_back(buffer);
            buffer.first = buffer.second = "";
        }

        buffer = keyValue;
    }

    if (!buffer.first.isEmpty()) {
        if (result.find(buffer.first) != result.end()) {
            logEntry<InfoSectionParserLogEntry>(
                LOG_ENTRY_TYPE::WARNING,
                QObject::tr("Attempting to add more than one value with the same key"),
                path,
                lineNumber);
        } else {
            result.insert(buffer);
        }
        if (keyValueVector)
            keyValueVector->push_back(buffer);
        buffer.first = buffer.second = "";
    }

    return result;
}
}
