#ifndef MODULEITEM_H
#define MODULEITEM_H

#include <QString>

enum class MODULE_ITEM_TYPE {
    NONE,
    SUBMODULE,
    LESSON
};

class ModuleItem {
public:
    ModuleItem(const QString& name);
    virtual ~ModuleItem();

    QString getName() const;
    void setName(const QString& value);

    MODULE_ITEM_TYPE getType() const;

protected:
    QString name;
    MODULE_ITEM_TYPE type = MODULE_ITEM_TYPE::NONE;
};

#endif // MODULEITEM_H
