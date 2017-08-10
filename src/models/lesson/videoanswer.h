#ifndef VIDEOANSWER_H
#define VIDEOANSWER_H

#include "mediaanswer.h"



class VideoAnswer : public MediaAnswer
{
public:
    VideoAnswer(const std::map<QString, QString>& keyValueMap);
};

#endif // VIDEOANSWER_H
