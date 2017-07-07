#ifndef SUBMODULE_H
#define SUBMODULE_H

#include "lesson.h"
#include "moduleitem.h"

#include <memory>
#include <vector>

class Submodule : public ModuleItem {
public:
    Submodule(const QString& name);

    void addLesson(std::shared_ptr<Lesson> lesson);

private:
    std::vector<std::shared_ptr<Lesson>> lessons;
};

#endif // SUBMODULE_H
