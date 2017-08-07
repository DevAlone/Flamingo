#ifndef AUDIOPAGE_H
#define AUDIOPAGE_H

#include "mediapage.h"



class AudioPage : public MediaPage
{
public:
    AudioPage(std::map<QString, QString>& infoSection);
};

#endif // AUDIOPAGE_H
