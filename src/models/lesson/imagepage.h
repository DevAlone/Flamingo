#ifndef IMAGEPAGE_H
#define IMAGEPAGE_H

#include "mediapage.h"

class ImagePage : public MediaPage {
public:
    ImagePage(std::map<QString, QString>& infoSection);

    virtual QJsonObject toJsonObject() const;

protected:
};

#endif // IMAGEPAGE_H
