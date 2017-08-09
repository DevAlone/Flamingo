#ifndef VIDEOCONTENT_H
#define VIDEOCONTENT_H

#include "mediacontent.h"

class VideoContent : public MediaContent {
public:
    VideoContent(const QString& source = "");

    QJsonObject toJsonObject() const;
};

#endif // VIDEOCONTENT_H
