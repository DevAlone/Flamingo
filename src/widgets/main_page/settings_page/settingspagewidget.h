#ifndef SETTINGSPAGEWIDGET_H
#define SETTINGSPAGEWIDGET_H

#include <QtWidgets>

#include <memory>

class SettingsPageWidgetUi;

class SettingsPageWidget : public QWidget {
    Q_OBJECT

    friend class SettingsPageWidgetUi;

public:
    explicit SettingsPageWidget(QWidget* parent = nullptr);

signals:
    void goToBackPage();
public slots:
    void activate();
    void saveButtonClicked();

private:
    std::unique_ptr<SettingsPageWidgetUi> ui;
};

class SettingsPageWidgetUi {
    friend class SettingsPageWidget;

public:
    SettingsPageWidgetUi(SettingsPageWidget* parent)
    {
        mainLayout = new QVBoxLayout;
        scrollArea = new QScrollArea(parent);
        settingsWidget = new QWidget(parent);
        settingsLayout = new QFormLayout;
        courseDirectory = new QLabel(
            QObject::tr("course directory"), parent);
        courseDirectoryValue = new QLineEdit(parent);
        pageAutoSwitchTrigger = new QCheckBox(
            QObject::tr("enable page autoswitch"), parent);
        pageAutoSwitchTime = new QLabel(
            QObject::tr("page auto switch time(in ms)"));
        pageAutoSwitchTimeValue = new QSpinBox(parent);
        pageAutoSwitchTimeValue->setRange(0, 60000);

        bottomLayout = new QHBoxLayout;
        saveButton = new QPushButton(
            QObject::tr("&Save and close"), parent);

        mainLayout->addWidget(scrollArea);
        mainLayout->addStretch();

        mainLayout->addLayout(bottomLayout);

        bottomLayout->addStretch();
        bottomLayout->addWidget(saveButton);

        settingsLayout->addRow(courseDirectory, courseDirectoryValue);
        settingsLayout->addWidget(pageAutoSwitchTrigger);
        settingsLayout->addRow(pageAutoSwitchTime, pageAutoSwitchTimeValue);

        scrollArea->setWidget(settingsWidget);
        scrollArea->setWidgetResizable(true);
        settingsWidget->setLayout(settingsLayout);

        parent->setLayout(mainLayout);

        pageAutoSwitchTrigger->setChecked(true);

        QObject::connect(
            pageAutoSwitchTrigger, &QCheckBox::stateChanged,
            pageAutoSwitchTimeValue, &QSpinBox::setEnabled);

        QObject::connect(
            saveButton, &QPushButton::clicked,
            parent, &SettingsPageWidget::saveButtonClicked);
    }

private:
    QVBoxLayout* mainLayout;

    QScrollArea* scrollArea;
    QWidget* settingsWidget;

    QFormLayout* settingsLayout;

    QLabel* courseDirectory;
    QLineEdit* courseDirectoryValue;

    QCheckBox* pageAutoSwitchTrigger;
    QLabel* pageAutoSwitchTime;
    QSpinBox* pageAutoSwitchTimeValue;

    QHBoxLayout* bottomLayout;
    QPushButton* saveButton;
};

#endif // SETTINGSPAGEWIDGET_H
