#include "moduleitem.h"

ModuleItem::ModuleItem(const QString& name)
    : name(name)
{
}

ModuleItem::~ModuleItem()
{
}

QString ModuleItem::getName() const
{
    return name;
}

void ModuleItem::setName(const QString& value)
{
    name = value;
}

MODULE_ITEM_TYPE ModuleItem::getType() const
{
    return type;
}
