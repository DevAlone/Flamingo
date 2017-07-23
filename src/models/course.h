#ifndef COURSE_H
#define COURSE_H

#include "module.h"

#include <QSqlError>
#include <QString>
#include <QVector>

#include <vector>

#include <models/model.h>

class Course : public Model {
public:
    Course(QString name);
    virtual operator QString() const;

    QString getName() const;
    void setName(const QString& value);
    void addModule(std::shared_ptr<Module> module);
    void addModules(std::vector<std::shared_ptr<Module>>& modules);

    QString getAuthor() const;
    void setAuthor(const QString& value);

    unsigned char getLevel() const;
    void setLevel(int value);

    std::vector<std::shared_ptr<Module>>& getModules();

    int getUserId() const;
    void setUserId(int value);

    virtual void save();
    virtual bool update();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    static QSqlError createTable();
    static std::vector<std::shared_ptr<Course>> getAll();
    static std::vector<std::shared_ptr<Course>> getByUserId(int userId);
    static std::vector<std::shared_ptr<Course>> filter(int userId = -1);

    QString getLanguageCode() const;
    void setLanguageCode(const QString& value);

    QString getDescription() const;
    void setDescription(const QString& value);

private:
    QString name = "";
    QString author = "";
    unsigned char level = 1;
    QString description = "";
    QString languageCode = "";
    std::vector<std::shared_ptr<Module>> modules;

    int userId = -1;
};

#endif // COURSE_H
