// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
