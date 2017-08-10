#ifndef LOGINPAGEWIDGET_H
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
