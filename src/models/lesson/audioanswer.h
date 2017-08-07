#ifndef AUDIOANSWER_H
#define AUDIOANSWER_H

#include "mediaanswer.h"



class AudioAnswer : public MediaAnswer
{
public:
    AudioAnswer(const std::map<QString, QString>& keyValueMap);
};

#endif // AUDIOANSWER_H
