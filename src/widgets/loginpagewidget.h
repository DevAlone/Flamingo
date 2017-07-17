#ifndef LOGINPAGEWIDGET_H
#define LOGINPAGEWIDGET_H

#include "createuserwidget.h"
#include "userlistwidget.h"

#include <QtWidgets>

class LoginPageWidgetUi;

class LoginPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoginPageWidget(QWidget* parent = nullptr);
    virtual ~LoginPageWidget();

signals:

public slots:

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

        userList = new UserListWidget(parent);
        createUserWidget = new CreateUserWidget(parent);

        userListScrollArea = new QScrollArea(parent);

        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        verticalLayout->addStretch();
        verticalLayout->addWidget(headerLabel);
        verticalLayout->addWidget(userListScrollArea);
        userListScrollArea->setWidget(userList);
        verticalLayout->addWidget(createUserWidget);
        verticalLayout->addStretch();

        parent->setLayout(horizontalLayout);

        QObject::connect(createUserWidget, SIGNAL(userCreated()),
            userList, SLOT(updateUsers()));
    }

private:
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout;
    QLabel* headerLabel;
    QScrollArea* userListScrollArea;
    UserListWidget* userList;
    CreateUserWidget* createUserWidget;
};

#endif // LOGINPAGEWIDGET_H
