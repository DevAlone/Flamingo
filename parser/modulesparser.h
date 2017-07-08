#ifndef MODULESPARSER_H
#define MODULESPARSER_H

#include "module.h"
#include "parserlogger.h"

#include <QtCore>

namespace parser {
class ModulesParser : public QObject {
    Q_OBJECT
public:
    explicit ModulesParser(QObject* parent = nullptr);

    std::vector<Module> parseDirectory(const QString& path);

    Module parseModule(const QString& modulePath);

    void setLogger(std::shared_ptr<ParserLogger>& logger);
signals:

public slots:

private:
    std::shared_ptr<ParserLogger> logger;
    template <typename T, typename... Args>
    void logEntry(Args... args)
    {
        if (logger)
            logger->addEntry(std::make_unique<T>(args...));
    }
};
}

#endif // MODULESPARSER_H
