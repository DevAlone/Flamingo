#ifndef QUESTION_H
#define QUESTION_H

class Question {
public:
    Question(unsigned number);

    unsigned getNumber() const;

    bool operator<(const Question& other) const;

private:
    const unsigned number;
};

#endif // QUESTION_H
