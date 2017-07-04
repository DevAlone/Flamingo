#ifndef MODULEITEM_H
#define MODULEITEM_H

#include <QString>

enum class MODULE_ITEM_TYPE {
    SUBMODULE,
    LESSON
};

class ModuleItem {
public:
    ModuleItem(const QString& name);
    virtual ~ModuleItem();

    QString getName() const;
    void setName(const QString& value);

protected:
    QString name;
    MODULE_ITEM_TYPE type;
};

#endif // MODULEITEM_H
