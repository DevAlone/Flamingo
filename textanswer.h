#ifndef TEXTANSWER_H
#define TEXTANSWER_H

#include "answer.h"

#include <vector>

class TextAnswer : public Answer {
public:
    TextAnswer(std::map<QString, QString> keyValueMap,
        std::vector<std::pair<QString, QString>>& keyValueVec);

    const QString& getContent() const;

protected:
    QString content;
};

#endif // TEXTANSWER_H
