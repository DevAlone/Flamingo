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


#ifndef TOPPANELWIDGET_H
#define TOPPANELWIDGET_H

#include "breadcrumbwidget.h"

#include <QtWidgets>

#include <memory>

class TopPanelWidgetUi;

class TopPanelWidget : public QFrame {
    Q_OBJECT

    friend class TopPanelWidgetUi;

public:
    explicit TopPanelWidget(QWidget* parent = nullptr);

signals:
    void openSettings();
public slots:

private slots:
    void menuButtonClicked();

public:
    std::unique_ptr<TopPanelWidgetUi> ui;
};

class TopPanelWidgetUi {
public:
    TopPanelWidgetUi(TopPanelWidget* parent)
    {
        mainLayout = new QHBoxLayout;

        backButton = new QPushButton(parent);
        backButton->setObjectName("backButton");

        menuButton = new QPushButton(parent);
        menuButton->setObjectName("menuButton");
        menuButton->setIcon(QIcon(":/icons/menu.png"));
        menuButton->setToolTip(
            QObject::tr("Open menu"));

        breadcrumb = new BreadcrumbWidget(parent);
        userNameWidget = new QLabel(parent);
        userNameWidget->setObjectName("userNameWidget");

        mainLayout->addWidget(backButton);
        mainLayout->addWidget(breadcrumb);
        mainLayout->addStretch();
        mainLayout->addWidget(userNameWidget);
        mainLayout->addWidget(menuButton);

        parent->setLayout(mainLayout);

        //        mainLayout->setContentsMargins(0, 0, 0, 0);
        parent->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            menuButton, &QPushButton::clicked,
            parent, &TopPanelWidget::menuButtonClicked);

        menu = new QMenu(parent);
        menuSettingsAction = new QAction(
            QObject::tr("&Settings"), menu);
        menuSettingsAction->setToolTip(
            QObject::tr("Open settings"));
        QObject::connect(
            menuSettingsAction, &QAction::triggered,
            parent, &TopPanelWidget::openSettings);
        menu->addAction(menuSettingsAction);
    }
    QHBoxLayout* mainLayout;

    QPushButton* backButton;
    BreadcrumbWidget* breadcrumb;
    QLabel* userNameWidget;
    QPushButton* menuButton;

    QMenu* menu;
    QAction* menuSettingsAction;
};

#endif // TOPPANELWIDGET_H
