#pragma once

#include "modellistdispatcher.h"

class CourseListDispatcher : public ModelListDispatcher {
public:
    CourseListDispatcher(bool showOnlyActive = true);

    virtual std::vector<std::shared_ptr<Model>> getItemList();

private:
    bool showOnlyActive;
};
