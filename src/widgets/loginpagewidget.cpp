#include "loginpagewidget.h"

LoginPageWidget::LoginPageWidget(QWidget* parent)
    : AbstractPageWidget(parent)
{
    ui = std::make_unique<LoginPageWidgetUi>(this);
}

LoginPageWidget::~LoginPageWidget()
{
}

//void LoginPageWidget::setActiveUserId(int userId)
//{
//    activeUserId = userId;
//}

//void LoginPageWidget::setActiveUserId(QModelIndex userIndex)
//{
//    ui->userList->setCurrentIndex(userIndex);

//    QVariant obj = ui->userListModel->data(userIndex);
//    if (!obj.isValid())
//        return;

//    User& user = obj.value<User&>();

//    setActiveUserId(user.getId());
//}

void LoginPageWidget::loginButtonClicked()
{
    std::shared_ptr<User> selectedUser;

    try {
        selectedUser = ui->userListView->getSelectedUser();
    } catch (...) {
        // TODO: make normal exception type

        QMessageBox::warning(this,
            tr("Error"),
            tr("Check user please!"));
        return;
    }
    if (!selectedUser) {
        QMessageBox::warning(this,
            tr("Error"),
            tr("1Check user please!"));
        return;
    }

    // TODO: check user and change page

    User::setActiveUserId(selectedUser->getId());

    emit loginAsUser(User::getActiveUser());
}

void LoginPageWidget::activate()
{
    // TODO: do something
    //    ui->userListModel->updateModel();
    ui->userListView->updateItems();
    //    setActiveUserId(ui->userListModel->index(0));
}
