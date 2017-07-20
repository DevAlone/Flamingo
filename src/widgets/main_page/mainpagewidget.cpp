#include "mainpagewidget.h"

MainPageWidget::MainPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new MainPageWidgetUi(this);

    BreadcrumbWidgetItem* item1
        = new BreadcrumbWidgetItem("home", "home", this);
    BreadcrumbWidgetItem* item2
        = new BreadcrumbWidgetItem("user", "user", this);
    BreadcrumbWidgetItem* item3
        = new BreadcrumbWidgetItem("tmp", "tmp", this);

    ui->breadcrumb->addItem(item1);
    ui->breadcrumb->addItem(item2);
    ui->breadcrumb->addItem(item3);
}

void MainPageWidget::backButtonClicked()
{
}

void MainPageWidget::activate()
{
    auto activeUser = User::getActiveUser();
    ui->userNameWidget->setText(activeUser->getName());

    // TODO: do some things
}
