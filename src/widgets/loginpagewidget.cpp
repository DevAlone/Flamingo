#include "loginpagewidget.h"

LoginPageWidget::LoginPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new LoginPageWidgetUi(this);
}

LoginPageWidget::~LoginPageWidget()
{
    delete ui;
}

void LoginPageWidget::setActiveUserId(int userId)
{
    UserModel::setActiveUserId(userId);
}

void LoginPageWidget::setActiveUserId(QModelIndex userIndex)
{
    setActiveUserId(userIndex.row());
}

void LoginPageWidget::loginButtonClicked()
{
    // TODO: check user and change page

    loginAsUser(UserModel::getActiveUserId());
}
