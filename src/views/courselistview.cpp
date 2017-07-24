#include "courselistview.h"
#include "courselistdispatcher.h"

CourseListView::CourseListView(QWidget* parent)
    : ModelListView(parent)
{
    dispatcher = std::make_shared<CourseListDispatcher>();
}

std::shared_ptr<Course> CourseListView::getSelectedCourse()
{
    return std::static_pointer_cast<Course>(getSelectedModel());
}
