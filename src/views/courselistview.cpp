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
        SLOT(tryToDeleteSelectedItem()));
    // &CourseListView::tryToDeleteSelectedItem);

    courseContextMenu.exec(globalPos);
}
