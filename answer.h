#ifndef ANSWER_H
#define ANSWER_H

#include <QString>

#include <map>
#include <memory>
#include <vector>

enum class ANSWER_TYPE { TEXT };

class Answer {
public:
    Answer() = delete;

    static std::shared_ptr<Answer> createAnswer(
        QChar letter,
        std::map<QString, QString>& keyValueMap,
        std::vector<std::pair<QString, QString>>& keyValueVec);

private:
    QChar letter;
    ANSWER_TYPE type;
};

#endif // ANSWER_H
