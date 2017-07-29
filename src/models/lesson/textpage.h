#ifndef TEXTPAGE_H
#define TEXTPAGE_H

#include "page.h"

#include <QString>

class TextPage : public Page {
public:
    // TODO: maybe make private
    TextPage(std::map<QString, QString>& infoSection);

    const QString& getContent() const;

    virtual QJsonObject toJsonObject() const;
    static std::shared_ptr<TextPage> fromJsonObject(const QJsonObject& obj);

protected:
    QString content;
    // QString source;
};

#endif // TEXTPAGE_H
