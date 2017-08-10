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



#include "helper.h"

CourseSingleView::CourseSingleView(QWidget* parent)
    : ModelSingleView(parent)
{
    ui = std::make_unique<CourseSingleViewUi>(this);
}

//void CourseSingleView::setModel(std::shared_ptr<Model>& model)
//{
//    std::shared_ptr<Course> coursePtr = std::dynamic_pointer_cast<Course>(model);
//    if (!coursePtr)
//        return;

//    ModelSingleView::setModel(model);
//    course = coursePtr;

//    updateData();
//}

void CourseSingleView::setCourse(std::shared_ptr<Course> coursePtr)
{
    course = coursePtr;
    ModelSingleView::setModel(coursePtr);
}

void CourseSingleView::updateData()
{
    if (!course)
        return;
    // TODO: update
    course->update();
    ui->courseNameValue->setText(returnValueOrPlaceholder(course->getName()));
    ui->courseAuthorValue->setText(returnValueOrPlaceholder(course->getAuthor()));
    ui->courseLevelValue->setText(QString::number(course->getLevel()));
    ui->courseLanguageValue->setText(
        returnValueOrPlaceholder(languageCodeToString(course->getLanguageCode())));

    ui->courseDescriptionValue->setText(returnValueOrPlaceholder(course->getDescription()));
}

std::shared_ptr<Course> CourseSingleView::getCourse() const
{
    return course;
}
