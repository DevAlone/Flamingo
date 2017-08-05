#ifndef PAGE_H
#define PAGE_H

#include "answer.h"
#include "rightanswers.h"

#include <QObject>
#include <QString>

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include <exceptions/pagecreatingerror.h>

enum class PAGE_TYPE : int {
    TEXT,
    HTML,
    IMAGE
};

const std::map<QString, PAGE_TYPE> pageTypesMap = {
    { "text", PAGE_TYPE::TEXT },
    { "html", PAGE_TYPE::HTML },
    { "image", PAGE_TYPE::IMAGE },
};

class Page {

public:
    Page() {}
    virtual ~Page() {}

    // Fabric method which creates page
    // method automatically detect type
    // and creates appropriate class from hierarchy.
    // If one of necessary keys is missing,
    // method can throw exception
    static std::shared_ptr<Page> createPage(
        unsigned pageNumber,
        std::map<QString, QString>& infoSectionMap,
        std::vector<std::pair<QString, QString>>& infoSectionVec,
        std::map<QChar, std::shared_ptr<Answer>>& answers);

    unsigned getNumber() const;

    PAGE_TYPE getType() const;

    const std::map<QChar, std::shared_ptr<Answer>>& getAnswers() const;

    virtual QJsonObject toJsonObject() const;
    static std::shared_ptr<Page> fromJsonObject(const QJsonObject& obj);

    const RightAnswers& getRightAnswers() const;

    unsigned char getCompleteness() const;
    void setCompleteness(unsigned char value);

protected:
    unsigned number = 0;
    PAGE_TYPE type;
    std::map<QChar, std::shared_ptr<Answer>> answers;
    //    QString rightAnswers;
    RightAnswers rightAnswers;
    // value from 0 to 100
    unsigned char completeness = 0;
};

#endif // PAGE_H
