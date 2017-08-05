#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

#include "page.h"

class MediaPage : public Page {
    friend class Page;
    friend class ImagePage;
    MediaPage(std::map<QString, QString>& infoSection);

public:
    virtual QJsonObject toJsonObject() const;

    QString getSource() const;
    void setSource(const QString& value);

protected:
    QString source = "";
};

#endif // MEDIAPAGE_H
