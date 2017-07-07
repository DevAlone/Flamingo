#ifndef MODULE_H
#define MODULE_H

#include "moduleitem.h"

#include <memory>
#include <vector>

class Module {
public:
    Module(const QString& name);

    QString getName() const;
    void setName(const QString& value);

    void addModuleItem(std::shared_ptr<ModuleItem> moduleItem);

    std::vector<std::shared_ptr<ModuleItem>>& getModuleItems();

private:
    QString name;
    std::vector<std::shared_ptr<ModuleItem>> moduleItems;
};

#endif // MODULE_H
