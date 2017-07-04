#ifndef MODULE_H
#define MODULE_H

#include "moduleitem.h"

#include <vector>

class Module {
public:
    Module(const QString& name);

    QString getName() const;
    void setName(const QString& value);

    void addModuleItem(ModuleItem& moduleItem);

private:
    QString name;
    std::vector<ModuleItem> moduleItems;
};

#endif // MODULE_H
