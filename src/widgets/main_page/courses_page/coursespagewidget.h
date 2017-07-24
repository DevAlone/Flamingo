#ifndef COURSESPAGEWIDGET_H
#define COURSESPAGEWIDGET_H

#include "availablecourseslistwidget.h"

#include <QtWidgets>

#include <views/courselistview.h>
#include <views/coursesingleview.h>

#include <memory>

#include <widgets/main_page/twocolumnswidget.h>

class CoursesPageWidgetUi;

class CoursesPageWidget : public QWidget {
    Q_OBJECT

    friend class CoursesPageWidgetUi;

public:
    explicit CoursesPageWidget(QWidget* parent = nullptr);

signals:
    void goToModulesPage(std::shared_ptr<Course> course);
public slots:
    void activate();

private:
    std::unique_ptr<CoursesPageWidgetUi> ui;

private slots:
    void addCourseButtonPressed();
    void selectedCourseChanged();
    void courseOpenButtonPressed();
};

class CoursesPageWidgetUi {
    friend class CoursesPageWidget;

public:
    CoursesPageWidgetUi(CoursesPageWidget* parent)
    {
        layout = new QHBoxLayout;
        //        verticalLayout = new QVBoxLayout;
        columns = new TwoColumnsWidget(parent);

        courseList = new CourseListView(parent);
        courseView = new CourseSingleView(parent);

        availableCoursesLayout = new QHBoxLayout;
        availableCoursesList = new AvailableCoursesListWidget(parent);
        addCourse = new QPushButton(QObject::tr("+"), parent);
        addCourse->setToolTip(QObject::tr("Add course to current user"));

        //        verticalLayout->addWidget(courseList);
        //        verticalLayout->addLayout(availableCoursesLayout);
        columns->addLeftWidget(courseList);
        columns->addLeftLayout(availableCoursesLayout);

        availableCoursesLayout->addWidget(availableCoursesList, 3);
        availableCoursesLayout->addWidget(addCourse, 1);

        columns->addRightWidget(courseView);
        layout->addWidget(columns);

        parent->setLayout(layout);

        QObject::connect(
            addCourse, &QPushButton::clicked,
            parent, &CoursesPageWidget::addCourseButtonPressed);

        QObject::connect(
            courseList, &CourseListView::selectionChanged,
            parent, &CoursesPageWidget::selectedCourseChanged);

        QObject::connect(
            courseView, &CourseSingleView::openButtonPressed,
            parent, &CoursesPageWidget::courseOpenButtonPressed);
    }

private:
    QHBoxLayout* layout;
    //    QVBoxLayout* verticalLayout;
    TwoColumnsWidget* columns;

    CourseListView* courseList;
    CourseSingleView* courseView;

    QHBoxLayout* availableCoursesLayout;
    AvailableCoursesListWidget* availableCoursesList;
    QPushButton* addCourse;
};

#endif // COURSESPAGEWIDGET_H
