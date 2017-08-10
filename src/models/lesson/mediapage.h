#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

#include "page.h"

#include <models/lesson/content/mediacontent.h>

class MediaPage : public Page {

public:
    MediaPage(const std::map<QString, QString>& infoSection);
    virtual QJsonObject toJsonObject() const;

    QString getSource() const;
    void setSource(const QString& value);

protected:
    MediaContent content;
};

#endif // MEDIAPAGE_H
