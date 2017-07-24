#ifndef MAINPAGEWIDGET_H
#define MAINPAGEWIDGET_H

#include "breadcrumbwidget.h"
#include "courses_page/coursespagewidget.h"
#include "modules_page/modulespagewidget.h"

#include <QtWidgets>

#include <memory>

#include <models/user.h>

#include <widgets/main_page/module_items_page/moduleitemspagewidget.h>

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
        topPanelLayout = new QHBoxLayout;

        backButton = new QPushButton(parent);
        breadcrumb = new BreadcrumbWidget;
        userNameWidget = new QLabel(parent);

        coursesPage = new CoursesPageWidget(parent);
        modulesPage = new ModulesPageWidget(parent);
        moduleItemsPage = new ModuleItemsPageWidget(parent);

        pages = new QStackedWidget(parent);
        pages->addWidget(coursesPage);
        pages->addWidget(modulesPage);
        pages->addWidget(moduleItemsPage);

        backButton->setText(QObject::tr("< Back"));

        topPanelLayout->addWidget(backButton);
        topPanelLayout->addWidget(breadcrumb);
        topPanelLayout->addStretch();
        topPanelLayout->addWidget(userNameWidget);

        verticalLayout->addLayout(topPanelLayout);
        verticalLayout->addWidget(pages);

        parent->setLayout(verticalLayout);

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
    }

private:
    QVBoxLayout* verticalLayout;
    QHBoxLayout* topPanelLayout;

    QPushButton* backButton;
    BreadcrumbWidget* breadcrumb;
    QLabel* userNameWidget;

    QStackedWidget* pages;

    CoursesPageWidget* coursesPage;
    ModulesPageWidget* modulesPage;
    ModuleItemsPageWidget* moduleItemsPage;
};

#endif // MAINPAGEWIDGET_H
