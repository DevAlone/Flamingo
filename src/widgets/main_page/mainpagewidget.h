#ifndef MAINPAGEWIDGET_H
#define MAINPAGEWIDGET_H

#include "breadcrumbwidget.h"

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

private:
    MainPageWidgetUi* ui;
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

        pages = new QStackedWidget(parent);

        backButton->setText(QObject::tr("< Back"));

        topPanelLayout->addWidget(backButton);
        topPanelLayout->addWidget(breadcrumb);
        topPanelLayout->addStretch();
        topPanelLayout->addWidget(userNameWidget);

        verticalLayout->addLayout(topPanelLayout);
        verticalLayout->addWidget(pages);

        parent->setLayout(verticalLayout);

        QObject::connect(backButton, SIGNAL(clicked(bool)),
            parent, SLOT(backButtonClicked()));
    }

private:
    QVBoxLayout* verticalLayout;
    QHBoxLayout* topPanelLayout;

    QPushButton* backButton;
    BreadcrumbWidget* breadcrumb;
    QLabel* userNameWidget;

    QStackedWidget* pages;
};

#endif // MAINPAGEWIDGET_H
