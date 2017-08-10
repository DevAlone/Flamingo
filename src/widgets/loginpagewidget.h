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


#define LOGINPAGEWIDGET_H

#include "abstractpagewidget.h"
#include "createuserwidget.h"

#include <QtWidgets>

#include <models/include.h>

#include <views/userlistview.h>

#include <memory>

class LoginPageWidgetUi;

class LoginPageWidget : public AbstractPageWidget {
    Q_OBJECT
public:
    explicit LoginPageWidget(QWidget* parent = nullptr);
    virtual ~LoginPageWidget();

signals:
    void loginAsUser(std::shared_ptr<User> user);
public slots:
    //    void setActiveUserId(int userId);
    //    void setActiveUserId(QModelIndex userIndex);
    void activate();

private slots:
    void loginButtonClicked();

private:
    std::unique_ptr<LoginPageWidgetUi> ui;
    int activeUserId = -1;
};

class LoginPageWidgetUi {
    friend class LoginPageWidget;

public:
    LoginPageWidgetUi(LoginPageWidget* parent)
    {
        wrapper = new QFrame(parent);
        wrapper->setObjectName("loginForm");
        loginLayout = new QVBoxLayout;
        headerLabel = new QLabel(
            QObject::tr("Choose username"), parent);
        headerLabel->setObjectName("headerLabel");
        headerLabel->setAlignment(Qt::AlignHCenter);

        horizontalLayout = new QHBoxLayout();
        verticalLayout = new QVBoxLayout();

        userListView = new UserListView(parent);

        createUserWidget = new CreateUserWidget(parent);

        loginButton = new QPushButton(parent);
        loginButton->setText(QObject::tr("Login"));

        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        verticalLayout->addStretch();
        verticalLayout->addWidget(wrapper);
        wrapper->setLayout(loginLayout);
        loginLayout->addWidget(headerLabel);
        loginLayout->addWidget(userListView);
        loginLayout->addWidget(createUserWidget);
        loginLayout->addWidget(loginButton);
        verticalLayout->addStretch();

        parent->setLayout(horizontalLayout);

        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setSpacing(0);

        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setSpacing(0);

        loginLayout->setContentsMargins(0, 0, 0, 0);
        loginLayout->setSpacing(10);

        QObject::connect(
            createUserWidget, &CreateUserWidget::userCreated,
            userListView, &UserListView::updateItems);

        QObject::connect(
            loginButton, SIGNAL(clicked(bool)),
            parent, SLOT(loginButtonClicked()));
    }

private:
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout;

    QFrame* wrapper;
    QVBoxLayout* loginLayout;
    QLabel* headerLabel;
    //    QScrollArea* userListScrollArea;
    //    UserListWidget* userList;
    //    QListView* userList;
    //    UserListModel* userListModel;
    UserListView* userListView;
    CreateUserWidget* createUserWidget;
    QPushButton* loginButton;
};

#endif // LOGINPAGEWIDGET_H
