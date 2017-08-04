#ifndef MAINPAGEWIDGET_H
#define MAINPAGEWIDGET_H

#include "breadcrumbwidget.h"
#include "courses_page/coursespagewidget.h"
#include "lesson_page/lessonpagewidget.h"
#include "modules_page/modulespagewidget.h"
#include "toppanelwidget.h"

#include <QtWidgets>

#include <memory>

#include <models/user.h>

#include <widgets/main_page/module_items_page/moduleitemspagewidget.h>

#include <models/lesson/lesson.h>

#include <widgets/main_page/settings_page/settingspagewidget.h>

class MainPageWidgetUi;

class MainPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainPageWidget(QWidget* parent = nullptr);
    virtual ~MainPageWidget();

signals:
    // signal generates when widget wants to close itself
    // for example when user press back button
    // in root path
    void backToPreviousPage();
public slots:
    void backButtonClicked();
    // calls when widget needs to be updated
    // for example on login
    void activate();
    void breadcrubFullPathChanged(const QString& fullPath);
    void goToCoursesPage();
    void goToModulesPage(std::shared_ptr<Course> course = std::shared_ptr<Course>());
    void goToModuleItemsPage(std::shared_ptr<Module> module = std::shared_ptr<Module>());
    void goToLessonPage(std::shared_ptr<Lesson> lesson = std::shared_ptr<Lesson>());

    void goToSettingsPage();

private:
    std::unique_ptr<MainPageWidgetUi> ui;

private slots:
};

class MainPageWidgetUi {
    friend class MainPageWidget;

public:
    MainPageWidgetUi(MainPageWidget* parent)
    {
        verticalLayout = new QVBoxLayout;
        //        topPanelLayout = new QHBoxLayout;
        topPanel = new TopPanelWidget(parent);

        backButton = topPanel->ui->backButton;
        breadcrumb = topPanel->ui->breadcrumb;
        userNameWidget = topPanel->ui->userNameWidget;

        coursesPage = new CoursesPageWidget(parent);
        modulesPage = new ModulesPageWidget(parent);
        moduleItemsPage = new ModuleItemsPageWidget(parent);
        lessonPage = new LessonPageWidget(parent);
        settingsPage = new SettingsPageWidget(parent);

        verticalLayout->addWidget(topPanel);

        pages = new QStackedWidget(parent);
        pages->addWidget(coursesPage);
        pages->addWidget(modulesPage);
        pages->addWidget(moduleItemsPage);
        pages->addWidget(lessonPage);
        pages->addWidget(settingsPage);

        backButton->setText(QObject::tr("< Back"));

        //        topPanelLayout->addWidget(backButton);
        //        topPanelLayout->addWidget(breadcrumb);
        //        topPanelLayout->addStretch();
        //        topPanelLayout->addWidget(userNameWidget);

        //        verticalLayout->addLayout(topPanelLayout);
        verticalLayout->addWidget(pages);

        parent->setLayout(verticalLayout);

        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setSpacing(0);

        //        topPanelLayout->setContentsMargins(10, 0, 10, 0);
        //        topPanelLayout->setSpacing(0);

        QObject::connect(
            backButton, &QPushButton::clicked,
            parent, &MainPageWidget::backButtonClicked);

        QObject::connect(
            breadcrumb, &BreadcrumbWidget::fullPathChanged,
            parent, &MainPageWidget::breadcrubFullPathChanged);

        QObject::connect(
            coursesPage, &CoursesPageWidget::goToModulesPage,
            parent, &MainPageWidget::goToModulesPage);

        QObject::connect(
            modulesPage, &ModulesPageWidget::goToModuleItemsPage,
            parent, &MainPageWidget::goToModuleItemsPage);

        QObject::connect(
            moduleItemsPage, &ModuleItemsPageWidget::goToLessonPage,
            parent, &MainPageWidget::goToLessonPage);

        QObject::connect(
            lessonPage, &LessonPageWidget::lessonFinished,
            parent, &MainPageWidget::backButtonClicked);

        QObject::connect(
            topPanel, &TopPanelWidget::openSettings,
            parent, &MainPageWidget::goToSettingsPage);
    }

private:
    QVBoxLayout* verticalLayout;
    //    QHBoxLayout* topPanelLayout;
    TopPanelWidget* topPanel;

    QPushButton* backButton;
    BreadcrumbWidget* breadcrumb;
    QLabel* userNameWidget;

    QStackedWidget* pages;

    CoursesPageWidget* coursesPage;
    ModulesPageWidget* modulesPage;
    ModuleItemsPageWidget* moduleItemsPage;
    LessonPageWidget* lessonPage;

    SettingsPageWidget* settingsPage;
};

#endif // MAINPAGEWIDGET_H
