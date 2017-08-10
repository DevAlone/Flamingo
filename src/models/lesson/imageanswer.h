#ifndef IMAGEANSWER_H
#define IMAGEANSWER_H

#include "answer.h"
#include "mediaanswer.h"

class ImageAnswer : public MediaAnswer {
public:
    ImageAnswer(const std::map<QString, QString>& keyValueMap);
};

#endif // IMAGEANSWER_H
