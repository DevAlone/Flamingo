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
    std::pair<size_t, size_t> getCompleteness();

    virtual void save();
    virtual bool update();
    virtual bool remove();

    QString serialize();
    static std::shared_ptr<Lesson> deserialize(const QString& data, const QString& name);
    void updateSerializedData(const QString& data);

    int getSubmoduleId() const;

    void setSubmoduleId(int value);

    QString getDescription() const;
    void setDescription(const QString& value);

    static QSqlError createTable();
    static std::vector<std::shared_ptr<Lesson>> getAll();
    static std::vector<std::shared_ptr<Lesson>> getByModuleId(int moduleId);
    static std::vector<std::shared_ptr<Lesson>> getBySubmoduleId(int submoduleId);
    static std::vector<std::shared_ptr<Lesson>> filter(int moduleId = -1, int submoduleId = -1);

protected:
    virtual void sqlInsert();
    virtual void sqlUpdate();

private:
    // TODO: change to set?
    std::map<unsigned, std::shared_ptr<Page>> pages;
    int submoduleId = -1;

    QString description;
};

#endif // LESSON_H
