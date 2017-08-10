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


#define MAINWIDGET_H

#include "loginpagewidget.h"

#include <QtWidgets>

#include <widgets/main_page/mainpagewidget.h>

#include <memory>

class MainWidgetUi;

class MainWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget* parent = nullptr);
    virtual ~MainWidget();

signals:

public slots:
    void backToLoginPage();
    void loginAsUser(std::shared_ptr<User> user);

private:
    std::unique_ptr<MainWidgetUi> ui;
};

class MainWidgetUi {
    friend class MainWidget;

public:
    MainWidgetUi(MainWidget* parent)
    {
        pages = new QStackedWidget(parent);

        loginPage = new LoginPageWidget(pages);
        // TODO: todo
        mainPage = new MainPageWidget(pages);

        pages->addWidget(loginPage);
        pages->addWidget(mainPage);

        pages->setCurrentWidget(loginPage);
        loginPage->activate();

        layout = new QHBoxLayout;
        layout->addWidget(pages);
        parent->setLayout(layout);

        layout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            loginPage, &LoginPageWidget::loginAsUser,
            parent, &MainWidget::loginAsUser);

        QObject::connect(
            mainPage, &MainPageWidget::backToPreviousPage,
            parent, &MainWidget::backToLoginPage);
    }

private:
    QHBoxLayout* layout;
    QStackedWidget* pages;
    LoginPageWidget* loginPage;
    MainPageWidget* mainPage;
};

#endif // MAINWIDGET_H
