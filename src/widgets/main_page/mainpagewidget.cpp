#include "mainpagewidget.h"

MainPageWidget::MainPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<MainPageWidgetUi>(this);
}

MainPageWidget::~MainPageWidget()
{
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
    goToCoursesPage();
}

void MainPageWidget::breadcrubFullPathChanged(const QString& fullPath)
{
    // TODO: do something
    const BreadcrumbWidgetItem* lastItem = ui->breadcrumb->getLastItem();

    QString pathItem = lastItem->getPathItem();

    if (pathItem == "courses")
        goToCoursesPage();
    else if (pathItem == "modules")
        goToModulesPage();
    else if (pathItem == "moduleItems")
        goToModuleItemsPage();
    else if (pathItem == "lesson")
        goToLessonPage();
}

void MainPageWidget::goToCoursesPage()
{
    // BUG: проверить, почему метод срабатывает дважды
    ui->pages->setCurrentWidget(ui->coursesPage);
    ui->coursesPage->activate();

    BreadcrumbWidgetItem* currentItem = new BreadcrumbWidgetItem("courses", "courses");

    if (ui->breadcrumb->getLastItem()->getPathItem() == currentItem->getPathItem()) {
        currentItem->deleteLater();
        return;
    }

    ui->breadcrumb->addItem(currentItem); //TODO: add
}

void MainPageWidget::goToModulesPage(std::shared_ptr<Course> course)
{ // TODO: do it
    ui->pages->setCurrentWidget(ui->modulesPage);
    ui->modulesPage->activate(course);

    BreadcrumbWidgetItem* currentItem = new BreadcrumbWidgetItem("modules", "modules");

    if (ui->breadcrumb->getLastItem()->getPathItem() == currentItem->getPathItem()) {
        currentItem->deleteLater();
        return;
    }

    ui->breadcrumb->addItem(currentItem);
}

void MainPageWidget::goToModuleItemsPage(std::shared_ptr<Module> module)
{
    ui->pages->setCurrentWidget(ui->moduleItemsPage);
    ui->moduleItemsPage->activate(module);

    BreadcrumbWidgetItem* currentItem = new BreadcrumbWidgetItem("moduleItems", "moduleItems");

    if (ui->breadcrumb->getLastItem()->getPathItem() == currentItem->getPathItem()) {
        currentItem->deleteLater();
        return;
    }

    ui->breadcrumb->addItem(currentItem);
}

void MainPageWidget::goToLessonPage(std::shared_ptr<Lesson> lesson)
{
    ui->pages->setCurrentWidget(ui->lessonPage);
    ui->lessonPage->activate(lesson);

    BreadcrumbWidgetItem* currentItem = new BreadcrumbWidgetItem("lesson", "lesson");

    if (ui->breadcrumb->getLastItem()->getPathItem() == currentItem->getPathItem()) {
        currentItem->deleteLater();
        return;
    }

    ui->breadcrumb->addItem(currentItem);
}
