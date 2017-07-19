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

    void addLesson(std::shared_ptr<Lesson> lesson);

    virtual void save();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    static QSqlError createTable();

private:
    std::vector<std::shared_ptr<Lesson>> lessons;
};

#endif // SUBMODULE_H
