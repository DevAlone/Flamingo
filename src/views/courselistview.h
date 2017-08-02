#ifndef COURSELISTVIEW_H
#define COURSELISTVIEW_H

#include "modellistview.h"

#include <QWidget>

#include <models/course.h>

class CourseListView : public ModelListView {
    Q_OBJECT
public:
    explicit CourseListView(QWidget* parent = nullptr);

    std::shared_ptr<Course> getSelectedCourse();

signals:

public slots:
    virtual void tryToDeleteSelectedItem();
    virtual void showContextMenu(const QPoint& position);
};

#endif // COURSELISTVIEW_H
