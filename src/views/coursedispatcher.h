#ifndef COURSEDISPATCHER_H
#define COURSEDISPATCHER_H

#include "modeldispatcher.h"

class CourseDispatcher : public ModelDispatcher {
public:
    CourseDispatcher(bool showOnlyActive = true);

    virtual std::vector<std::shared_ptr<Model>> getItems();

private:
    bool showOnlyActive;
};

#endif // COURSEDISPATCHER_H
