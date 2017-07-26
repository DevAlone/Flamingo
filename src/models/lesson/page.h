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

enum class PAGE_TYPE {
    TEXT,
    HTML
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
        std::map<QString, QString>& infoSection,
        std::map<QChar, std::shared_ptr<Answer>>& answers);

    unsigned getNumber() const;

    PAGE_TYPE getType() const;

    const std::map<QChar, std::shared_ptr<Answer>>& getAnswers() const;

    virtual QJsonObject toJsonObject() const;
    static std::shared_ptr<Page> fromJsonObject(const QJsonObject& obj);

protected:
    unsigned number;
    PAGE_TYPE type;
    //std::vector<std::shared_ptr<Answer>> answers;
    std::map<QChar, std::shared_ptr<Answer>> answers;
    //    QString rightAnswers;
    RightAnswers rightAnswers;
};

#endif // PAGE_H
