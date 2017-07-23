#include "courselistview.h"
#include "coursedispatcher.h"

CourseListView::CourseListView(QWidget* parent)
    : ModelListView(parent)
{
    dispatcher = std::make_shared<CourseDispatcher>();
}

std::shared_ptr<Course> CourseListView::getSelectedCourse()
{
    return std::static_pointer_cast<Course>(getSelectedModel());
}
