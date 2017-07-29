#ifndef ANSWER_H
#define ANSWER_H

#include <QString>

#include <QJsonObject>
#include <map>
#include <memory>
#include <vector>

enum class ANSWER_TYPE {
    TEXT,
    HTML
};

class Answer {

public:
    Answer();
    virtual ~Answer();
    static std::shared_ptr<Answer> createAnswer(
        QChar letter,
        std::map<QString, QString>& keyValueMap,
        std::vector<std::pair<QString, QString>>& keyValueVec);

    ANSWER_TYPE getType() const;

    virtual QJsonObject toJsonObject() const;
    static std::shared_ptr<Answer> fromJsonObject(const QJsonObject& obj);

private:
    QChar letter;
    ANSWER_TYPE type;
};

#endif // ANSWER_H
