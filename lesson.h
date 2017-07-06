#ifndef LESSON_H
#define LESSON_H

#include "moduleitem.h"
#include "question.h"

#include <vector>

class Lesson : public ModuleItem {
public:
    Lesson(const QString& name);

    void addQuestion(const Question& question);

    std::vector<Question>& getQuestions();

private:
    std::vector<Question> questions;
};

#endif // LESSON_H
