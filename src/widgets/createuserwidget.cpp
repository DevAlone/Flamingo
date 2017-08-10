#include "createuserwidget.h"

#include <models/user.h>

CreateUserWidget::CreateUserWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<CreateUserWidgetUi>(this);
}

CreateUserWidget::~CreateUserWidget()
{
}

void CreateUserWidget::createButtonClicked()
{
    QString userName = ui->userNameLineEdit->text();

    if (userName.isEmpty()) {
        QMessageBox::warning(this,
            tr("Warning"),
            tr("User name cannot be empty"));
        //        ui->userNameLineEdit->setStyleSheet("QLineEdit { background: rgb(255, 100, 100); }");
        return;
    }
    //    ui->userNameLineEdit->setStyleSheet("");

    //    if (UserManager::getInstance()->addUser(userName))
    //        emit userCreated();

    User user;
    user.setName(userName);
    user.save();

    emit userCreated();
    // TODO: handle error
}
