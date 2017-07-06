#include "course.h"

Course::Course(QString name)
    : name(name)
{
}

QString Course::getName() const
{
    return name;
}

void Course::setName(const QString& value)
{
    name = value;
}

void Course::addModule(Module& module)
{
    modules.push_back(module);
}

void Course::addModules(std::vector<Module>& modules)
{
    for (auto& module : modules)
        addModule(module);
}

QString Course::getAuthor() const
{
    return author;
}

void Course::setAuthor(const QString& value)
{
    author = value;
}

unsigned char Course::getLevel() const
{
    return level;
}

void Course::setLevel(unsigned char value)
{
    level = value;
}

std::vector<Module>& Course::getModules()
{
    return modules;
}
