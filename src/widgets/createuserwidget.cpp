#include "createuserwidget.h"

#include <db/usermanager.h>

#include <models/usermodel.h>

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

    UserModel user;
    user.setName(userName);
    if (user.save())
        emit userCreated();
    // TODO: handle error
}
