#ifndef AUDIOCONTENT_H
#define AUDIOCONTENT_H

#include "mediacontent.h"



class AudioContent : public MediaContent
{
public:
    AudioContent(const QString& source = "");

    virtual QJsonObject toJsonObject() const;
};

#endif // AUDIOCONTENT_H
