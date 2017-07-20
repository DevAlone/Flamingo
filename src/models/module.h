#ifndef MODULE_H
#define MODULE_H

#include "moduleitem.h"

#include <QSqlError>
#include <memory>
#include <vector>

#include <models/model.h>

class Module : public Model {
public:
    Module(const QString& name);
    Module(const Module& other);
    Module& operator=(const Module& other);
    virtual operator QString() const;

    QString getName() const;
    void setName(const QString& value);

    void addModuleItem(std::shared_ptr<ModuleItem> moduleItem);

    std::vector<std::shared_ptr<ModuleItem>>& getModuleItems();

    int getCourseId() const;
    void setCourseId(int value);

    virtual void save();
    virtual void sqlInsert();
    virtual void sqlUpdate();
    static QSqlError createTable();

private:
    QString name;
    std::vector<std::shared_ptr<ModuleItem>> moduleItems;

    int courseId = -1;
};

#endif // MODULE_H
