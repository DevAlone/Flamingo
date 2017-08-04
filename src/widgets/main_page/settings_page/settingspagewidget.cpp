#include "settingspagewidget.h"

SettingsPageWidget::SettingsPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<SettingsPageWidgetUi>(this);
}

void SettingsPageWidget::activate()
{
}
