#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "loginpagewidget.h"

#include <QtWidgets>

class MainWidgetUi;

class MainWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget* parent = nullptr);
    virtual ~MainWidget();

signals:

public slots:

private:
    MainWidgetUi* ui = nullptr;
};

class MainWidgetUi {
public:
    MainWidgetUi(MainWidget* parent)
    {
        pages = new QStackedWidget(parent);

        loginPage = new LoginPageWidget(pages);
        // TODO: todo
        mainPage = new QWidget(pages);

        pages->addWidget(loginPage);
        pages->addWidget(mainPage);

        pages->setCurrentWidget(loginPage);

        layout = new QHBoxLayout;
        layout->addWidget(pages);
        parent->setLayout(layout);
    }

private:
    QHBoxLayout* layout;
    QStackedWidget* pages;
    LoginPageWidget* loginPage;
    QWidget* mainPage;
};

#endif // MAINWIDGET_H
