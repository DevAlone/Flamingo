#include "courselistdispatcher.h"

#include <models/course.h>
#include <models/user.h>

CourseListDispatcher::CourseListDispatcher(bool showOnlyActive)
    : showOnlyActive(showOnlyActive)
{
}

std::vector<std::shared_ptr<Model>> CourseListDispatcher::getItemList()
{
    int userId = showOnlyActive ? User::getActiveUserId() : -1;

    std::vector<std::shared_ptr<Course>> courses = Course::filter(userId);
    std::vector<std::shared_ptr<Model>> models;

    if (showOnlyActive && userId == -1)
        return models;

    for (auto& course : courses)
        models.push_back(std::static_pointer_cast<Model>(course));

    return models;
}
