#ifndef MAINWIDGET_H
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
