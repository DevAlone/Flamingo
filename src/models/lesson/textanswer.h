#ifndef TEXTANSWER_H
#define TEXTANSWER_H

#include "answer.h"

#include <vector>

#include <models/lesson/content/textcontent.h>

class TextAnswer : public Answer {
public:
    TextAnswer(const std::map<QString, QString>& keyValueMap);

    const QString& getContent() const;

    virtual QJsonObject toJsonObject() const;

protected:
    TextContent content;
};

#endif // TEXTANSWER_H
