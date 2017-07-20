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

    unsigned char getLevel() const;
    void setLevel(unsigned char value);

    virtual void save();

    static QSqlError createTable();

    QString serialize();
    static Lesson deserialize(const QString& data, const QString& name);

    int getSubmoduleId() const;

    void setSubmoduleId(int value);

protected:
    virtual void sqlInsert();
    virtual void sqlUpdate();

private:
    std::map<unsigned, std::shared_ptr<Page>> pages;
    unsigned char level = 1;
    int submoduleId = -1;

    // Model interface
public:
};

#endif // LESSON_H
