#ifndef MODULESPARSER_H
#define MODULESPARSER_H

#include "module.h"

#include <QtCore>

namespace parser {
class ModulesParser : public QObject {
    Q_OBJECT
public:
    explicit ModulesParser(QObject* parent = nullptr);

    std::vector<Module> parseDirectory(const QString& path);

    Module parseModule(const QString& modulePath);

signals:

public slots:
};
}

#endif // MODULESPARSER_H
