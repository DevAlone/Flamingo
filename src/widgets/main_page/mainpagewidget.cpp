#include "mainpagewidget.h"

MainPageWidget::MainPageWidget(QWidget* parent)
    : AbstractPageWidget(parent)
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
    setPage(ui->coursesPage);

    setLastBreadcrumbItem("courses", tr("courses"));
}

void MainPageWidget::goToModulesPage(std::shared_ptr<Course> course)
{
    setPage(ui->modulesPage);
    if (course)
        ui->modulesPage->setCourse(course);

    setLastBreadcrumbItem("modules", tr("modules"));
}

void MainPageWidget::goToModuleItemsPage(std::shared_ptr<Module> module)
{
    setPage(ui->moduleItemsPage);
    if (module)
        ui->moduleItemsPage->setModule(module);

    setLastBreadcrumbItem("moduleItems", tr("lessons and submodules"));
}

void MainPageWidget::goToLessonPage(std::shared_ptr<Lesson> lesson)
{
    setPage(ui->lessonPage);
    if (lesson)
        ui->lessonPage->setLesson(lesson);

    setLastBreadcrumbItem("lesson", tr("lesson"));
}

void MainPageWidget::goToSettingsPage()
{
    setPage(ui->settingsPage);

    setLastBreadcrumbItem("settings", tr("settings"));
}

void MainPageWidget::setPage(AbstractPageWidget* page)
{
    auto currentWidget = ui->pages->currentWidget();
    if (currentWidget) {
        auto currentPage = qobject_cast<AbstractPageWidget*>(currentWidget);
        if (currentPage) {
            currentPage->deactivate();
        }
    }
    ui->pages->setCurrentWidget(page);
    page->activate();
}

void MainPageWidget::setLastBreadcrumbItem(const QString& path, const QString& name)
{
    // Острожно, костыли!
    QSignalBlocker blocker(ui->breadcrumb);

    BreadcrumbWidgetItem* currentItem = new BreadcrumbWidgetItem(path, name);

    if (ui->breadcrumb->getLastItem()->getPathItem() == currentItem->getPathItem()) {
        currentItem->deleteLater();
        return;
    }

    ui->breadcrumb->addItem(currentItem);
}
