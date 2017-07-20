#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new MainWidgetUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
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
