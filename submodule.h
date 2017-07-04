#ifndef SUBMODULE_H
#define SUBMODULE_H

#include "lesson.h"
#include "moduleitem.h"

#include <vector>

class Submodule : public ModuleItem {
public:
    Submodule(const QString& name);

    void addLesson(const Lesson& lesson);

private:
    std::vector<Lesson> lessons;
};

#endif // SUBMODULE_H
