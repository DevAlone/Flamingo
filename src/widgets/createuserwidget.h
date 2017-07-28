#ifndef CREATEUSERWIDGET_H
#define CREATEUSERWIDGET_H

#include <QtWidgets>

#include <memory>

class CreateUserWidgetUi;

class CreateUserWidget : public QWidget {
    Q_OBJECT
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

        QObject::connect(createButton, SIGNAL(clicked(bool)),
            parent, SLOT(createButtonClicked()));
    }

    QHBoxLayout* layout;
    QLineEdit* userNameLineEdit;
    QPushButton* createButton;
};

#endif // CREATEUSERWIDGET_H
