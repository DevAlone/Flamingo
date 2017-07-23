#include "coursesingleview.h"

CourseSingleView::CourseSingleView(QWidget* parent)
    : ModelSingleView(parent)
{
    ui = std::make_unique<CourseSingleViewUi>(this);
}

void CourseSingleView::setModel(std::shared_ptr<Model>& model)
{
    std::shared_ptr<Course> coursePtr = std::dynamic_pointer_cast<Course>(model);
    if (!coursePtr)
        return;

    ModelSingleView::setModel(model);
    course = coursePtr;

    updateData();
}

void CourseSingleView::setCourse(std::shared_ptr<Course> coursePtr)
{
    course = coursePtr;
    model = coursePtr;

    updateData();
}

void CourseSingleView::updateData()
{
    if (!course)
        return;
    // TODO: update
    course->update();
    ui->courseNameValue->setText(course->getName());
    ui->courseAuthorValue->setText(course->getAuthor());
    ui->courseLevelValue->setText(QString::number(course->getLevel()));
}

std::shared_ptr<Course> CourseSingleView::getCourse() const
{
    return course;
}
