#ifndef VIDEOPAGE_H
#define VIDEOPAGE_H

#include "mediapage.h"



class VideoPage : public MediaPage
{
public:
    VideoPage(std::map<QString, QString>& infoSection);
};

#endif // VIDEOPAGE_H
