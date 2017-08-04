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

public slots:
    void activate();

private:
    std::unique_ptr<SettingsPageWidgetUi> ui;
};

class SettingsPageWidgetUi {
    friend class SettingsPageWidget;

public:
    SettingsPageWidgetUi(SettingsPageWidget* parent)
    {
        mainLayout = new QVBoxLayout;

        mainLayout->addWidget(new QLabel("test settings"));

        parent->setLayout(mainLayout);
    }

private:
    QVBoxLayout* mainLayout;
};

#endif // SETTINGSPAGEWIDGET_H
