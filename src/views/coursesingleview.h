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


#ifndef COURSESINGLEVIEW_H
#define COURSESINGLEVIEW_H

#include "modelsingleview.h"

#include <QtWidgets>

#include <models/course.h>

#include <memory>

class CourseSingleViewUi;

class CourseSingleView : public ModelSingleView {
    Q_OBJECT
public:
    explicit CourseSingleView(QWidget* parent = nullptr);

    virtual void setModel(std::shared_ptr<Model>& model) = delete;
    void setCourse(std::shared_ptr<Course> coursePtr);

    std::shared_ptr<Course> getCourse() const;

signals:
    void openButtonPressed();

public slots:
    void updateData();

protected:
    std::shared_ptr<Course> course;

private:
    std::unique_ptr<CourseSingleViewUi> ui;
};

class CourseSingleViewUi {
    friend class CourseSingleView;

public:
    CourseSingleViewUi(CourseSingleView* parent)
    {
        mainLayout = new QVBoxLayout;
        topLayout = new QHBoxLayout;
        keyValueData = new QFormLayout;

        startButton = new QPushButton(QObject::tr("Open"), parent);

        courseNameValue = new QLabel(parent);

        courseAuthor
            = new QLabel(QObject::tr("Author"), parent);
        courseAuthorValue = new QLabel(parent);

        courseLevel
            = new QLabel(QObject::tr("Level"), parent);
        courseLevelValue = new QLabel(parent);

        courseLanguage
            = new QLabel(QObject::tr("Language"), parent);
        courseLanguageValue = new QLabel(parent);

        courseDescription
            = new QLabel(QObject::tr("Description"), parent);
        courseDescriptionValue = new QLabel(parent);
        courseDescriptionValue->setWordWrap(true);

        topLayout->addWidget(courseNameValue);
        topLayout->addWidget(startButton);

        keyValueData->addRow(courseAuthor, courseAuthorValue);
        keyValueData->addRow(courseLevel, courseLevelValue);
        keyValueData->addRow(courseLanguage, courseLanguageValue);

        mainLayout->addLayout(topLayout);
        mainLayout->addLayout(keyValueData);
        mainLayout->addWidget(courseDescription);
        mainLayout->addWidget(courseDescriptionValue);
        mainLayout->addStretch();

        parent->setLayout(mainLayout);

        mainLayout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            startButton, &QPushButton::clicked,
            parent, &CourseSingleView::openButtonPressed);
    }

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* topLayout;
    QFormLayout* keyValueData;

    QPushButton* startButton;

    //    QLabel *courseName;
    QLabel* courseNameValue;

    QLabel* courseAuthor;
    QLabel* courseAuthorValue;

    QLabel* courseLevel;
    QLabel* courseLevelValue;

    QLabel* courseLanguage;
    QLabel* courseLanguageValue;

    QLabel* courseDescription;
    QLabel* courseDescriptionValue;
};

#endif // COURSESINGLEVIEW_H
