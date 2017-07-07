#ifndef LESSON_H
#define LESSON_H

#include "moduleitem.h"
#include "question.h"

#include <map>
#include <memory>
#include <vector>

class Lesson : public ModuleItem {
public:
    Lesson(const QString& name);

    bool addQuestion(std::shared_ptr<Question>& question);

    std::map<unsigned, std::shared_ptr<Question>>& getQuestions();

    unsigned char getLevel() const;
    void setLevel(unsigned char value);

private:
    std::map<unsigned, std::shared_ptr<Question>> questions;
    unsigned char level;
};

#endif // LESSON_H
