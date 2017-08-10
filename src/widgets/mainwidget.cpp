#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<MainWidgetUi>(this);
}

MainWidget::~MainWidget()
{
}

void MainWidget::backToLoginPage()
{
    ui->pages->setCurrentWidget(ui->loginPage);
    ui->loginPage->activate();
}

void MainWidget::loginAsUser(std::shared_ptr<User> user)
{
    // TODO: check and so on

    // prepare main page
    ui->pages->setCurrentWidget(ui->mainPage);
    ui->mainPage->activate();
}
