#ifndef ANSWER_H
#define ANSWER_H

#include <QString>

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
    static std::shared_ptr<Answer> createAnswer(
        QChar letter,
        std::map<QString, QString>& keyValueMap,
        std::vector<std::pair<QString, QString>>& keyValueVec);

    ANSWER_TYPE getType() const;

private:
    QChar letter;
    ANSWER_TYPE type;
};

#endif // ANSWER_H
