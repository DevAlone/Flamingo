#include "lesson.h"

Lesson::Lesson(const QString& name)
    : ModuleItem(name)
{
    type = MODULE_ITEM_TYPE::LESSON;
}

void Lesson::addQuestion(const Question& question)
{
    questions.push_back(question);
}

std::vector<Question>& Lesson::getQuestions()
{
    return questions;
}
