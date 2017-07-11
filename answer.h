#ifndef ANSWER_H
#define ANSWER_H

enum class ANSWER_TYPE { TEXT };

class Answer {
public:
    Answer() = delete;

private:
    char letter;
    ANSWER_TYPE type;
};

#endif // ANSWER_H
