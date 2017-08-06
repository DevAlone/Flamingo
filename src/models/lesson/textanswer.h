#ifndef TEXTANSWER_H
#define TEXTANSWER_H

#include "answer.h"

#include <vector>

class TextAnswer : public Answer {
public:
    TextAnswer(const std::map<QString, QString>& keyValueMap);

    const QString& getContent() const;

    virtual QJsonObject toJsonObject() const;

protected:
    QString content;
};

#endif // TEXTANSWER_H
