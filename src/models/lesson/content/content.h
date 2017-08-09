#ifndef CONTENT_H
#define CONTENT_H

#include <QJsonObject>

#include <memory>

enum class CONTENT_TYPE {
    TEXT,
    HTML,
    MEDIA,
    IMAGE,
    AUDIO,
    VIDEO,
    NONE
};

class Content {
public:
    Content();

    static std::shared_ptr<Content> fromKeyValue(
        const QString& key,
        const QString& value);

    virtual QJsonObject toJsonObject() const;

    CONTENT_TYPE getType() const;

protected:
    CONTENT_TYPE type = CONTENT_TYPE::NONE;
};

#endif // CONTENT_H
