#ifndef MAINPAGEWIDGET_H
#define MAINPAGEWIDGET_H

#include "breadcrumbwidget.h"
#include "coursespagewidget.h"

#include <QtWidgets>

#include <memory>

#include <models/user.h>

class MainPageWidgetUi;

class MainPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainPageWidget(QWidget* parent = nullptr);

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

private:
    MainPageWidgetUi* ui;

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
        breadcrumb = new BreadcrumbWidget(parent);
        userNameWidget = new QLabel(parent);

        coursesPage = new CoursesPageWidget(parent);
        pages = new QStackedWidget(parent);
        pages->addWidget(coursesPage);

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
    }

private:
    QVBoxLayout* verticalLayout;
    QHBoxLayout* topPanelLayout;

    QPushButton* backButton;
    BreadcrumbWidget* breadcrumb;
    QLabel* userNameWidget;

    QStackedWidget* pages;

    CoursesPageWidget* coursesPage;
};

#endif // MAINPAGEWIDGET_H
