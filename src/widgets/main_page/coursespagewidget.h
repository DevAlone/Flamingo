#ifndef COURSESPAGEWIDGET_H
#define COURSESPAGEWIDGET_H

#include "availablecourseslistwidget.h"

#include <QtWidgets>

#include <views/courselistview.h>

class CoursesPageWidgetUi;

class CoursesPageWidget : public QWidget {
    Q_OBJECT

    friend class CoursesPageWidgetUi;

public:
    explicit CoursesPageWidget(QWidget* parent = nullptr);

signals:

public slots:
    void activate();

private:
    CoursesPageWidgetUi* ui;

private slots:
    void addCourseButtonPressed();
};

class CoursesPageWidgetUi {
    friend class CoursesPageWidget;

public:
    CoursesPageWidgetUi(CoursesPageWidget* parent)
    {
        layout = new QHBoxLayout;
        verticalLayout = new QVBoxLayout;
        courseList = new CourseListView(parent);
        availableCoursesLayout = new QHBoxLayout;
        availableCoursesList = new AvailableCoursesListWidget(parent);
        addCourse = new QPushButton(QObject::tr("+"), parent);
        addCourse->setToolTip(QObject::tr("Add course to current user"));

        verticalLayout->addWidget(courseList);
        verticalLayout->addLayout(availableCoursesLayout);
        availableCoursesLayout->addWidget(availableCoursesList);
        availableCoursesLayout->addWidget(addCourse);

        layout->addLayout(verticalLayout);

        //        layout->addLayout(courseView);

        parent->setLayout(layout);

        QObject::connect(
            addCourse, &QPushButton::clicked,
            parent, &CoursesPageWidget::addCourseButtonPressed);
    }

private:
    QHBoxLayout* layout;
    QVBoxLayout* verticalLayout;

    CourseListView* courseList;

    QHBoxLayout* availableCoursesLayout;
    AvailableCoursesListWidget* availableCoursesList;
    QPushButton* addCourse;
};

#endif // COURSESPAGEWIDGET_H
