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


#include "availablecourseslistwidget.h"

#include <parser/coursesparser.h>

#include <functional>

AvailableCoursesListWidget::AvailableCoursesListWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<AvailableCoursesListWidgetUi>(this);

    updateItems();
}

QString AvailableCoursesListWidget::getSelectedCourseName() const
{
    return ui->courseList->currentText();
}

void AvailableCoursesListWidget::updateItems()
{
    // TODO: переписать этот говнокод
    QString text = ".";
    for (int i = 0; i < 3; i++, text += ".") {
        ui->updateButton->setText(text);
        QTime endTime = QTime::currentTime().addMSecs(100);
        while (QTime::currentTime() < endTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    ui->updateButton->setText("⟳");

    parser::CoursesParser parser;
    // TODO: add logger?

    QSettings s;
    QString dir = s.value("courseParser/courseDirectory").toString();
    items = parser.listCoursesInDirectory(dir);

    ui->courseList->clear();

    for (auto& item : items)
        ui->courseList->addItem(item);

    ui->courseList->setCurrentIndex(0);
}
