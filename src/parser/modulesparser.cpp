#include "modulesparser.h"
#include "lessonsparser.h"
#include "logger/modulesparserlogentry.h"
#include "models/include.h"

namespace parser {

std::vector<Module> ModulesParser::parseDirectory(const QString& path)
{
    logEntry<ModulesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of modules directory was started"),
        path);

    std::vector<Module> modules;

    QDir baseDir(path);

    if (!baseDir.exists()) {
        logEntry<ModulesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Directory ") + path + QObject::tr(" doesn't exist"),
            path);

        return modules;
    }

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
    logEntry<ModulesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of module directory was started"),
        modulePath);

    Module module(modulePath); // TODO: ?

    QDir moduleDir(modulePath);

    if (!moduleDir.exists()) {
        // it shouldn't happen
        logEntry<ModulesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Directory ") + modulePath + QObject::tr(" doesn't exist"));
        return module;
    }

    auto entries = moduleDir.entryList(
        QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks,
        QDir::Name);

    LessonsParser lessonsParser;
    lessonsParser.setLogger(logger);

    for (auto& entry : entries) {
        QString entryPath = moduleDir.absoluteFilePath(entry);

        QFileInfo fileInfo(entryPath);

        if (fileInfo.isFile()) {
            auto lesson = lessonsParser.parseFile(entryPath);

            module.addModuleItem(lesson);
        } else if (fileInfo.isDir()) {
            logEntry<ModulesParserLogEntry>(
                LOG_ENTRY_TYPE::INFO,
                QObject::tr("Parsing of submodule directory was started"),
                entryPath);

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
                auto lesson = lessonsParser.parseFile(entryPath);

                submodule->addLesson(lesson);
            }
            module.addModuleItem(submodule);
        }
    }

    return module;
}
}
