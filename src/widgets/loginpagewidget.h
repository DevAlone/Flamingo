#ifndef LOGINPAGEWIDGET_H
#define LOGINPAGEWIDGET_H

#include "createuserwidget.h"

#include <QtWidgets>

#include <models/include.h>

#include <views/userlistview.h>

#include <memory>

class LoginPageWidgetUi;

class LoginPageWidget : public QWidget {
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
        headerLabel = new QLabel("Войти", parent);

        horizontalLayout = new QHBoxLayout();
        verticalLayout = new QVBoxLayout();

        userListView = new UserListView(parent);
        //        userList = new UserListWidget(parent);
        //        userList = new QListView(parent);
        //        userListModel = new UserListModel(parent);
        //        userList->setModel(userListModel);

        createUserWidget = new CreateUserWidget(parent);

        loginButton = new QPushButton(parent);
        loginButton->setText(QObject::tr("Login"));

        //        userListScrollArea = new QScrollArea(parent);

        horizontalLayout->addStretch();
        horizontalLayout->addLayout(verticalLayout);
        horizontalLayout->addStretch();

        verticalLayout->addStretch();
        verticalLayout->addWidget(headerLabel);
        verticalLayout->addWidget(userListView);
        //        verticalLayout->addWidget(userList);
        //        verticalLayout->addWidget(userListScrollArea);
        //        userListScrollArea->setWidget(userList);
        verticalLayout->addWidget(createUserWidget);
        verticalLayout->addWidget(loginButton);
        verticalLayout->addStretch();

        parent->setLayout(horizontalLayout);

        QObject::connect(createUserWidget, &CreateUserWidget::userCreated,
            userListView, &UserListView::updateItems);

        QObject::connect(loginButton, SIGNAL(clicked(bool)),
            parent, SLOT(loginButtonClicked()));
    }

private:
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout;
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
