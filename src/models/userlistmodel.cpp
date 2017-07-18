#include "userlistmodel.h"
#include "user.h"

UserListModel::UserListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    updateModel();
}

void UserListModel::updateModel()
{
    userList = User::getAll();
    emit dataChanged(QModelIndex(), QModelIndex());
}

int UserListModel::rowCount(const QModelIndex& parent) const
{
    return userList.size();
}

QVariant UserListModel::data(const QModelIndex& index, int role) const
{
    // TODO: optimize
    if (!index.isValid())
        return QVariant();

    if (index.row() >= userList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return userList.at(index.row())->getName();
    } else if (role == Qt::BackgroundRole) {
        // TODO: ?
        //        int batch = (index.row() / 100) % 2;
        //        if (batch == 0)
        //            return qApp->palette().base();
        //        else
        //            return qApp->palette().alternateBase();
        return QVariant();
    }
    return QVariant();
}
