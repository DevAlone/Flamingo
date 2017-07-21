#include "coursespagewidget.h"

CoursesPageWidget::CoursesPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new CoursesPageWidgetUi(this);
}

void CoursesPageWidget::activate()
{
}

void CoursesPageWidget::addCourseButtonPressed()
{
    // TODO: add course to current user

    QString selectedCourse = ui->availableCoursesList->getSelectedCourseName();
    if (selectedCourse.isEmpty()) {
        QMessageBox::warning(this,
            QObject::tr("Warning"),
            QObject::tr("Choose course, please"));
        return;
    }
    // TODO: add course
}
