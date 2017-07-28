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

    virtual void setModel(std::shared_ptr<Model>& model);
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
