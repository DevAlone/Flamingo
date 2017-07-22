#include "modulespagewidget.h"

ModulesPageWidget::ModulesPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<ModulesPageWidgetUi>(this);
}

void ModulesPageWidget::activate(std::shared_ptr<Course> course)
{
    if (course) {
        // update modules
    }
}
