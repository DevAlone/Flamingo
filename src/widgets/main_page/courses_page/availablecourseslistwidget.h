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


#ifndef AVAILABLECOURSESLISTWIDGET_H
#define AVAILABLECOURSESLISTWIDGET_H

#include <QtWidgets>

#include <memory>

class AvailableCoursesListWidgetUi;

class AvailableCoursesListWidget : public QWidget {
    Q_OBJECT
public:
    explicit AvailableCoursesListWidget(QWidget* parent = nullptr);

    QString getSelectedCourseName() const;
signals:

public slots:
    void updateItems();

private:
    std::vector<QString> items;
    std::unique_ptr<AvailableCoursesListWidgetUi> ui;
};

class AvailableCoursesListWidgetUi {
    friend class AvailableCoursesListWidget;

public:
    AvailableCoursesListWidgetUi(AvailableCoursesListWidget* parent)
    {
        layout = new QHBoxLayout;
        updateButton = new QPushButton(QObject::tr("⟳", "update courses button"), parent);
        updateButton->setToolTip("update course list");

        courseList = new QComboBox(parent);
        layout->addWidget(updateButton, 1);
        layout->addWidget(courseList, 5);

        parent->setLayout(layout);

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(5);

        QObject::connect(
            updateButton, &QPushButton::clicked,
            parent, &AvailableCoursesListWidget::updateItems);
    }

private:
    QHBoxLayout* layout;
    QPushButton* updateButton;
    QComboBox* courseList;
};

#endif // AVAILABLECOURSESLISTWIDGET_H
