#ifndef LOGINPAGEWIDGET_H
#define LOGINPAGEWIDGET_H

#include "createuserwidget.h"
#include "userlistwidget.h"

#include <QtWidgets>

#include <models/userlistmodel.h>
#include <models/usermodel.h>

class LoginPageWidgetUi;

class LoginPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoginPageWidget(QWidget* parent = nullptr);
    virtual ~LoginPageWidget();

signals:
    void loginAsUser(int userId);
public slots:
    void setActiveUserId(int userId);
    void setActiveUserId(QModelIndex userIndex);

private slots:
    void loginButtonClicked();

private:
    LoginPageWidgetUi* ui = nullptr;
};

class LoginPageWidgetUi {
public:
    LoginPageWidgetUi(LoginPageWidget* parent)
    {
        headerLabel = new QLabel("Войти", parent);

        horizontalLayout = new QHBoxLayout();
        verticalLayout = new QVBoxLayout();

        //        userList = new UserListWidget(parent);
        userList = new QListView(parent);
        UserListModel* userListModel = new UserListModel(parent);
        userList->setModel(userListModel);

        createUserWidget = new CreateUserWidget(parent);

        loginButton = new QPushButton(parent);
        loginButton->setText(QObject::tr("Login"));

        //        userListScrollArea = new QScrollArea(parent);

        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        verticalLayout->addStretch();
        verticalLayout->addWidget(headerLabel);
        verticalLayout->addWidget(userList);
        //        verticalLayout->addWidget(userListScrollArea);
        //        userListScrollArea->setWidget(userList);
        verticalLayout->addWidget(createUserWidget);
        verticalLayout->addWidget(loginButton);
        verticalLayout->addStretch();

        parent->setLayout(horizontalLayout);

        QObject::connect(createUserWidget, SIGNAL(userCreated()),
            userListModel, SLOT(updateModel()));
        QObject::connect(createUserWidget, SIGNAL(userCreated()),
            userList, SLOT(update()));

        QObject::connect(userList, SIGNAL(activated(QModelIndex)),
            parent, SLOT(setActiveUserId(QModelIndex)));
        QObject::connect(userList, SIGNAL(clicked(QModelIndex)),
            parent, SLOT(setActiveUserId(QModelIndex)));

        QObject::connect(loginButton, SIGNAL(clicked(bool)),
            parent, SLOT(loginButtonClicked()));
    }

private:
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout;
    QLabel* headerLabel;
    //    QScrollArea* userListScrollArea;
    //    UserListWidget* userList;
    QListView* userList;
    CreateUserWidget* createUserWidget;
    QPushButton* loginButton;
};

#endif // LOGINPAGEWIDGET_H
