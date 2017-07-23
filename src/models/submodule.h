#ifndef SUBMODULE_H
#define SUBMODULE_H

#include "lesson/include.h"
#include "moduleitem.h"

#include <QSqlError>
#include <memory>
#include <vector>

class Submodule : public ModuleItem {
public:
    Submodule(const QString& name);
    Submodule(const Submodule& other);
    Submodule& operator=(const Submodule& other);
    virtual operator QString() const;

    void addLesson(std::shared_ptr<Lesson> lesson);

    virtual void save();
    virtual bool update();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    static QSqlError createTable();
    static std::vector<std::shared_ptr<Submodule>> getAll();
    static std::vector<std::shared_ptr<Submodule>> getByModuleId(int moduleId);
    static std::vector<std::shared_ptr<Submodule>> filter(int moduleId = -1);

private:
    std::vector<std::shared_ptr<Lesson>> lessons;
};

#endif // SUBMODULE_H
