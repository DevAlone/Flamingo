#ifndef MEDIAANSWER_H
#define MEDIAANSWER_H

#include "answer.h"

#include <models/lesson/content/mediacontent.h>

class MediaAnswer : public Answer {
public:
    MediaAnswer(const std::map<QString, QString>& keyValueMap);

    virtual QJsonObject toJsonObject() const;

    QString getSource() const;
    void setSource(const QString& value);

protected:
    MediaContent content;
};

#endif // MEDIAANSWER_H
