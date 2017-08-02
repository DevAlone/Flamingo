#ifndef USERMODEL_H
#define USERMODEL_H

#include "model.h"

#include <QObject>

#include <QSqlError>
#include <memory>
#include <models/course.h>
#include <vector>

class User : public Model {
public:
    User();
    virtual operator QString() const;

    QString getName() const;
    void setName(const QString& name);

    static QSqlError createTable();
    static std::vector<std::shared_ptr<User>> getAll();

    static void setActiveUserId(int userId);
    static int getActiveUserId();
    static std::shared_ptr<User> getActiveUser();

    virtual void save();
    virtual bool update();
    virtual bool remove();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    std::vector<std::shared_ptr<Course>>& getCourses();

protected:
    QString name = "";
    std::vector<std::shared_ptr<Course>> courses;
};
struct UserPrivate {

    static int activeUserId;
    static std::shared_ptr<User> activeUser;
};

#endif // USERMODEL_H
