#include "settingspagewidget.h"

SettingsPageWidget::SettingsPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<SettingsPageWidgetUi>(this);
}

void SettingsPageWidget::activate()
{
    QSettings s;

    ui->courseDirectoryValue->setText(
        s.value("courseParser/courseDirectory", "courses").toString());
    auto autoSwitchTime = s.value("interface/lesson/pageAutoSwitchTime", 500).toInt();
    ui->pageAutoSwitchTrigger->setChecked(autoSwitchTime >= 0);
    if (autoSwitchTime >= 0)
        ui->pageAutoSwitchTimeValue->setValue(autoSwitchTime);
}

void SettingsPageWidget::saveButtonClicked()
{
    QSettings s;
    s.setValue("courseParser/courseDirectory", ui->courseDirectoryValue->text());

    if (ui->pageAutoSwitchTrigger->isChecked())
        s.setValue("interface/lesson/pageAutoSwitchTime", ui->pageAutoSwitchTimeValue->value());
    else
        s.setValue("interface/lesson/pageAutoSwitchTime", -1);

    emit goToBackPage();
}
