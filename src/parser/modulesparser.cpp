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
#include "lessonsparser.h"
#include "logger/modulesparserlogentry.h"
#include "models/include.h"

namespace parser {

std::vector<std::shared_ptr<Module> > ModulesParser::parseDirectory(const QString& path)
{
    logEntry<ModulesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of modules directory was started"),
        path);

    std::vector<std::shared_ptr<Module> > modules;

    QDir baseDir(path);

    QDir modulesDir = baseDir;

    if (!modulesDir.exists()) {
        logEntry<ModulesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Directory ") + path + QObject::tr(" doesn't exist"),
            path);

        return modules;
    }

    auto entries = modulesDir.entryList(
        QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks,
        QDir::Name);

    for (auto& entry : entries) {
        QString moduleDirPath = modulesDir.absoluteFilePath(entry);

        QFileInfo fileInfo(moduleDirPath);

        if (!fileInfo.isDir())
            continue;

        auto module = parseModule(moduleDirPath);

        modules.push_back(module);
    }

    return modules;
}

std::shared_ptr<Module> ModulesParser::parseModule(const QString& modulePath)
{
    logEntry<ModulesParserLogEntry>(
        LOG_ENTRY_TYPE::INFO,
        QObject::tr("Parsing of module directory was started"),
        modulePath);

    auto module = std::make_shared<Module>(modulePath); // TODO: ?

    QDir moduleDir(modulePath);

    if (!moduleDir.exists()) {
        // it shouldn't happen
        logEntry<ModulesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Directory ") + modulePath + QObject::tr(" doesn't exist"));
        return module;
    }

    module->setName(moduleDir.dirName());

    //parse info file

    QString infoFilePath = moduleDir.absoluteFilePath("info.txt");

    InfoSectionParser infoFileParser;
    infoFileParser.setLogger(logger);

    std::map<QString, QString> infoFileMap = infoFileParser.parseInfoFile(infoFilePath);

    for (auto& keyValue : infoFileMap) {
        const auto& key = keyValue.first;
        const auto& value = keyValue.second;

        if (key == "name") {
            module->setName(value);
        } else if (key == "description") {
            module->setDescription(value);
        } else if (key == "level") {
            bool isOk;
            int number = value.toInt(&isOk);
            if (!isOk || number < 1 || number > 10) {
                logEntry<ModulesParserLogEntry>(
                    LOG_ENTRY_TYPE::ERROR,
                    QObject::tr("Module level must be number from 1 to 10 (included): \n\t")
                        + value,
                    infoFilePath);
            } else {
                module->setLevel(number);
            }
        }
    }

    // parse items

    QDir moduleItemsDir = moduleDir.absoluteFilePath("items");

    if (!moduleItemsDir.exists()) {
        logEntry<ModulesParserLogEntry>(
            LOG_ENTRY_TYPE::ERROR,
            QObject::tr("Directory ") + moduleItemsDir.absolutePath()
                + QObject::tr(" doesnt' exist"));
        return module;
    }

    auto entries = moduleItemsDir.entryList(
        QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks,
        QDir::Name);

    LessonsParser lessonsParser;
    lessonsParser.setLogger(logger);

    for (auto& entry : entries) {
        QString entryPath = moduleItemsDir.absoluteFilePath(entry);

        QFileInfo fileInfo(entryPath);

        if (fileInfo.isFile()) {
            auto lesson = lessonsParser.parseFile(entryPath);

            module->addModuleItem(lesson);
        } else if (fileInfo.isDir()) {
            logEntry<ModulesParserLogEntry>(
                LOG_ENTRY_TYPE::INFO,
                QObject::tr("Parsing of submodule directory was started"),
                entryPath);

            QDir submoduleDir(entryPath);

            auto submodule = std::make_shared<Submodule>(submoduleDir.dirName());

            auto submoduleEntries = submoduleDir.entryList(
                QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                QDir::Name);

            for (auto& submoduleEntry : submoduleEntries) {
                QString submoduleEntryPath = submoduleDir.absoluteFilePath(submoduleEntry);

                QFileInfo submoduleEntryFileInfo(submoduleEntryPath);

                if (!submoduleEntryFileInfo.isFile())
                    continue;

                auto lesson = lessonsParser.parseFile(submoduleEntryPath);

                submodule->addLesson(lesson);
            }
            module->addModuleItem(submodule);
        }
    }

    return module;
}
}
