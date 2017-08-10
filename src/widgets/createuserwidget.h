#ifndef CREATEUSERWIDGET_H
#define CREATEUSERWIDGET_H

#include <QtWidgets>

#include <memory>

class CreateUserWidgetUi;

class CreateUserWidget : public QWidget {
    Q_OBJECT

    friend class CreateUserWidgetUi;

public:
    explicit CreateUserWidget(QWidget* parent = nullptr);
    virtual ~CreateUserWidget();

signals:
    void userCreated();

public slots:

private slots:
    void createButtonClicked();

private:
    std::unique_ptr<CreateUserWidgetUi> ui;
};

class CreateUserWidgetUi {
    friend class CreateUserWidget;

public:
    CreateUserWidgetUi(CreateUserWidget* parent)
    {
        layout = new QHBoxLayout;
        userNameLineEdit = new QLineEdit;
        userNameLineEdit->setPlaceholderText(
            QObject::tr("Enter username here"));
        createButton = new QPushButton("+", parent);
        createButton->setToolTip(QObject::tr("Add user"));

        layout->addWidget(userNameLineEdit);
        layout->addWidget(createButton);

        parent->setLayout(layout);

        layout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            createButton, &QPushButton::clicked,
            parent, &CreateUserWidget::createButtonClicked);

        QObject::connect(
            userNameLineEdit, &QLineEdit::returnPressed,
            createButton, &QPushButton::click);
    }

    QHBoxLayout* layout;
    QLineEdit* userNameLineEdit;
    QPushButton* createButton;
};

#endif // CREATEUSERWIDGET_H
