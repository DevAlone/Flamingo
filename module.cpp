#include "module.h"

Module::Module(const QString& name)
    : name(name)
{
}

QString Module::getName() const
{
    return name;
}

void Module::setName(const QString& value)
{
    name = value;
}

void Module::addModuleItem(std::shared_ptr<ModuleItem> moduleItem)
{
    moduleItems.push_back(moduleItem);
}

std::vector<std::shared_ptr<ModuleItem> >& Module::getModuleItems()
{
    return moduleItems;
}
