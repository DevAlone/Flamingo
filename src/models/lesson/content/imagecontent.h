#ifndef IMAGECONTENT_H
#define IMAGECONTENT_H

#include "mediacontent.h"



class ImageContent : public MediaContent
{
public:
    ImageContent(const QString& source = "");

    virtual QJsonObject toJsonObject() const;
};

#endif // IMAGECONTENT_H
