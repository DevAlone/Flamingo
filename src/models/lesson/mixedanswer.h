#ifndef MIXEDANSWER_H
#define MIXEDANSWER_H

#include "answer.h"

#include <models/lesson/content/content.h>

class MixedAnswer : public Answer {
public:
    MixedAnswer(const std::map<QString, QString>& keyValueMap,
        const std::vector<std::pair<QString, QString>>& keyValueVec);

    virtual QJsonObject toJsonObject() const;

    const std::vector<std::shared_ptr<Content>>& getContents() const;

private:
    std::vector<std::shared_ptr<Content>> contents;
};

#endif // MIXEDANSWER_H
