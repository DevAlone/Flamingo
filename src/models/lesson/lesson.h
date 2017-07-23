#ifndef LESSON_H
#define LESSON_H

#include "models/moduleitem.h"
#include "page.h"

#include <QSqlError>
#include <map>
#include <memory>
#include <vector>

// TODO: save to database like serialized string
class Lesson : public ModuleItem {
public:
    Lesson(const QString& name);
    virtual operator QString() const;

    bool addPage(std::shared_ptr<Page>& page);

    std::map<unsigned, std::shared_ptr<Page>>& getPages();

    virtual void save();
    virtual bool update();

    QString serialize();
    static std::shared_ptr<Lesson> deserialize(const QString& data, const QString& name);

    int getSubmoduleId() const;

    void setSubmoduleId(int value);

    static QSqlError createTable();
    static std::vector<std::shared_ptr<Lesson>> getAll();
    static std::vector<std::shared_ptr<Lesson>> getByModuleId(int moduleId);
    static std::vector<std::shared_ptr<Lesson>> getBySubmoduleId(int submoduleId);
    static std::vector<std::shared_ptr<Lesson>> filter(int moduleId = -1, int submoduleId = -1);

protected:
    virtual void sqlInsert();
    virtual void sqlUpdate();

private:
    std::map<unsigned, std::shared_ptr<Page>> pages;
    //    unsigned char level = 1;
    int submoduleId = -1;

    // Model interface
public:
};

#endif // LESSON_H
