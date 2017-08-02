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

void CourseListView::tryToDeleteSelectedItem()
{
    auto selectedCourse = getSelectedCourse();
    if (!selectedCourse)
        return;

    if (QMessageBox::question(this,
            QObject::tr("Delete course?"),
            QObject::tr("Are you sure you want to delete this course?")
                + "\n " + selectedCourse->getName(),
            QMessageBox::Yes | QMessageBox::No)
        == QMessageBox::Yes) {
        selectedCourse->remove();
        updateItems();
    }
}

void CourseListView::showContextMenu(const QPoint& position)
{
    QPoint globalPos = ui->listWidget->mapToGlobal(position);

    QMenu courseContextMenu;
    courseContextMenu.addAction(
        QObject::tr("Delete selected course"),
        this,
        &CourseListView::tryToDeleteSelectedItem);

    courseContextMenu.exec(globalPos);
}
