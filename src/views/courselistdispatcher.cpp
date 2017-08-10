// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
