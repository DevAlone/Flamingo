#include "mainpagewidget.h"

MainPageWidget::MainPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new MainPageWidgetUi(this);

    //    BreadcrumbWidgetItem* item1
    //        = new BreadcrumbWidgetItem("home", "home", this);
    //    BreadcrumbWidgetItem* item2
    //        = new BreadcrumbWidgetItem("user", "user", this);
    //    BreadcrumbWidgetItem* item3
    //        = new BreadcrumbWidgetItem("tmp", "tmp", this);

    //    ui->breadcrumb->addItem(item1);
    //    ui->breadcrumb->addItem(item2);
    //    ui->breadcrumb->addItem(item3);
}

void MainPageWidget::backButtonClicked()
{
    if (!ui->breadcrumb->cdUp())
        emit backToPreviousPage();
}

void MainPageWidget::activate()
{
    auto activeUser = User::getActiveUser();
    ui->userNameWidget->setText(activeUser->getName());

    ui->breadcrumb->clear();
    BreadcrumbWidgetItem* rootItem
        = new BreadcrumbWidgetItem("root", "courses", this);
    ui->breadcrumb->addItem(rootItem);
}

void MainPageWidget::breadcrubFullPathChanged(const QString& fullPath)
{
    // TODO: do something
    const BreadcrumbWidgetItem* lastItem = ui->breadcrumb->getLastItem();

    QString pathItem = lastItem->getPathItem();

    if (pathItem == "root") {
        ui->pages->setCurrentWidget(ui->coursesPage);
        ui->coursesPage->activate();
    }
}
