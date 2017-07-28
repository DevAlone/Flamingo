#ifndef TOPPANELWIDGET_H
#define TOPPANELWIDGET_H

#include "breadcrumbwidget.h"

#include <QtWidgets>

#include <memory>

class TopPanelWidgetUi;

class TopPanelWidget : public QFrame {
    Q_OBJECT
public:
    explicit TopPanelWidget(QWidget* parent = nullptr);

signals:

public slots:

public:
    std::unique_ptr<TopPanelWidgetUi> ui;
};

class TopPanelWidgetUi {
public:
    TopPanelWidgetUi(TopPanelWidget* parent)
    {
        mainLayout = new QHBoxLayout;

        backButton = new QPushButton(parent);
        breadcrumb = new BreadcrumbWidget(parent);
        userNameWidget = new QLabel(parent);

        mainLayout->addWidget(backButton);
        mainLayout->addWidget(breadcrumb);
        mainLayout->addStretch();
        mainLayout->addWidget(userNameWidget);

        parent->setLayout(mainLayout);
    }
    QHBoxLayout* mainLayout;

    QPushButton* backButton;
    BreadcrumbWidget* breadcrumb;
    QLabel* userNameWidget;
};

#endif // TOPPANELWIDGET_H
