#include "createuserwidget.h"

#include <models/user.h>

CreateUserWidget::CreateUserWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new CreateUserWidgetUi(this);
}

CreateUserWidget::~CreateUserWidget()
{
    delete ui;
}

void CreateUserWidget::createButtonClicked()
{
    QString userName = ui->userNameLineEdit->text();

    //    if (UserManager::getInstance()->addUser(userName))
    //        emit userCreated();

    User user;
    user.setName(userName);
    user.save();

    emit userCreated();
    // TODO: handle error
}
