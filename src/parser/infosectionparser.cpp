#include "infosectionparser.h"

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
