#include "lesson.h"

Lesson::Lesson(const QString& name)
    : ModuleItem(name)
{
    type = MODULE_ITEM_TYPE::LESSON;
}

bool Lesson::addQuestion(std::shared_ptr<Question>& question)
{
    if (questions.find(question->getNumber()) != questions.end()) {
        // if question with same number is already in here
        return false;
    }

    questions.insert(std::make_pair(
        question->getNumber(),
        question));
    return true;
}

std::map<unsigned, std::shared_ptr<Question>>& Lesson::getQuestions()
{
    return questions;
}

unsigned char Lesson::getLevel() const
{
    return level;
}

void Lesson::setLevel(unsigned char value)
{
    level = value;
}
