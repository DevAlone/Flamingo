#include "modulesparser.h"
#include "lessonsparser.h"
#include "submodule.h"

#include <exceptions/modulesparserexception.h>

namespace parser {
ModulesParser::ModulesParser(QObject* parent)
    : QObject(parent)
{
}

std::vector<Module> ModulesParser::parseDirectory(const QString& path)
{
    std::vector<Module> modules;

    QDir baseDir(path);

    if (!baseDir.exists())
        throw ModulesParserException(
            tr("Directory ") + path + tr(" doesn't exist"));

    auto entries = baseDir.entryList(
        QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks,
        QDir::Name);

    for (auto& entry : entries) {
        QString moduleDirPath = baseDir.absoluteFilePath(entry);

        QFileInfo fileInfo(moduleDirPath);

        if (!fileInfo.isDir())
            continue;

        Module module = parseModule(moduleDirPath);

        modules.push_back(module);
    }

    return modules;
}

Module ModulesParser::parseModule(const QString& modulePath)
{
    Module module(modulePath); // TODO: ?

    QDir moduleDir(modulePath);

    if (!moduleDir.exists())
        throw ModulesParserException(
            tr("Directory ") + modulePath + tr(" doesn't exist"));

    auto entries = moduleDir.entryList(
        QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks,
        QDir::Name);

    for (auto& entry : entries) {
        QString entryPath = moduleDir.absoluteFilePath(entry);

        QFileInfo fileInfo(entryPath);

        if (fileInfo.isFile()) {
            qDebug() << "file: " << entryPath;
            auto lesson = LessonsParser::parseFile(entryPath);

            module.addModuleItem(lesson);
        } else if (fileInfo.isDir()) {
            qDebug() << "dir: " << entryPath;

            QDir submoduleDir(entryPath);

            auto submodule = std::make_shared<Submodule>(entryPath); // TODO: ?

            auto submoduleEntries = submoduleDir.entryList(
                QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                QDir::Name);

            for (auto& submoduleEntry : submoduleEntries) {
                QString submoduleEntryPath = submoduleDir.absoluteFilePath(submoduleEntry);

                QFileInfo submoduleFileInfo(submoduleEntryPath);

                if (!submoduleFileInfo.isFile())
                    continue;
                auto lesson = LessonsParser::parseFile(entryPath);

                // TODO: parse lesson
                submodule->addLesson(lesson);
            }
            module.addModuleItem(submodule);
        }
    }

    return module;
}
}
