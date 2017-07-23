#ifndef MODULEITEM_H
#define MODULEITEM_H

#include "model.h"

#include <QString>

#include <memory>
#include <vector>

enum class MODULE_ITEM_TYPE {
    NONE,
    SUBMODULE,
    LESSON
};

class ModuleItem : public Model {
public:
    ModuleItem(const QString& name);
    virtual ~ModuleItem();

    QString getName() const;
    void setName(const QString& value);

    MODULE_ITEM_TYPE getType() const;

    virtual void save() = 0;

    int getModuleId() const;
    void setModuleId(int value);

    static std::vector<std::shared_ptr<ModuleItem>> getAll();
    static std::vector<std::shared_ptr<ModuleItem>> getByModuleId(int moduleId);
    static std::vector<std::shared_ptr<ModuleItem>> filter(int moduleId = -1);

protected:
    QString name = "";
    MODULE_ITEM_TYPE type = MODULE_ITEM_TYPE::NONE;
    int moduleId = -1;
};

#endif // MODULEITEM_H
