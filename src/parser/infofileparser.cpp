#include "infofileparser.h"

#include <parser/logger/infofileparserlogentry.h>

namespace parser {
std::map<QString, QString> InfoFileParser::parseFile(const QString& path)
{
    logEntry<InfoFileParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of info file was started"),
        path);

    QFile infoFile(path);

    std::map<QString, QString> result;
    if (!infoFile.exists()) {
        logEntry<InfoFileParserLogEntry>(
            LOG_ENTRY_TYPE::WARNING,
            QObject::tr("info.txt file wasn't found here: ")
                + path);
    } else if (!infoFile.open(QIODevice::ReadOnly)) {
        logEntry<InfoFileParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("info.txt can't be opened. "
                        "Maybe you don't have permissions to do that"),
            path);

    } else {
        logEntry<InfoFileParserLogEntry>(
            LOG_ENTRY_TYPE::INFO,
            QObject::tr("Parsing of info file was started"),
            path);

        std::pair<QString, QString> buffer
            = std::make_pair<QString, QString>("", "");

        QTextStream stream(&infoFile);
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
                    logEntry<InfoFileParserLogEntry>(
                        LOG_ENTRY_TYPE::ERROR,
                        QObject::tr("Attempting to add more than one value with the same key"),
                        path,
                        lineNumber);
                } else {
                    result.insert(buffer);
                }
                buffer.first = buffer.second = "";
            }

            buffer = keyValue;
        }
        infoFile.close();

        if (!buffer.first.isEmpty()) {
            if (result.find(buffer.first) != result.end()) {
                logEntry<InfoFileParserLogEntry>(
                    LOG_ENTRY_TYPE::ERROR,
                    QObject::tr("Attempting to add more than one value with the same key"),
                    path,
                    lineNumber);
            } else {
                result.insert(buffer);
            }
            buffer.first = buffer.second = "";
        }
    }
    return result;
}
}
