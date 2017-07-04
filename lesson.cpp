#include "lesson.h"

Lesson::Lesson(const QString& name)
    : ModuleItem(name)
{
}

void Lesson::addQuestion(const Question& question)
{
    questions.push_back(question);
}
