#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>

#include <QSqlError>
#include <memory>
#include <vector>

class UserModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)

public:
    explicit UserModel(QObject* parent = nullptr);

    QString name() const;
    void setName(const QString& name);

    static QSqlError createTable();
    static std::vector<std::shared_ptr<UserModel>> getAll();

    static void setActiveUserId(int userId);
    static int getActiveUserId();

    bool save();

    int id() const;

signals:

public slots:

private:
    int _id = -1;
    QString _name;
};
static int activeUserId = -1;

#endif // USERMODEL_H
