#include "userlistwidget.h"
#include "userlistitemwidget.h"

#include <db/usermanager.h>

#include <models/usermodel.h>

UserListWidget::UserListWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new UserListWidgetUi(this);

    updateUsers();
}

UserListWidget::~UserListWidget()
{
    delete ui;
}

void UserListWidget::updateUsers()
{
    //    delete ui->layout;

    //    ui->layout = new QVBoxLayout;

    //    setLayout(ui->layout);

    for (auto& user : UserModel::getAll()) {
        UserListItemWidget* widget = new UserListItemWidget(std::make_pair<QVariant, QString>(user->id(), user->name()), this);

        ui->layout->addWidget(widget);
        // TODO: users.push_back
    }

    // TODO: do it!!!!!!
    //    for (const auto& user : UserManager::getInstance()->getUserList()) {
    //        UserListItemWidget* widget = new UserListItemWidget(user, this);

    //        ui->layout->addWidget(widget);
    //        // TODO: users.push_back();
    //    }

    update();
}
