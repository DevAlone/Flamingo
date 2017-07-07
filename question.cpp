#include "question.h"

Question::Question(unsigned number)
    : number(number)
{
}

unsigned Question::getNumber() const
{
    return number;
}

bool Question::operator<(const Question& other) const
{
    return number < other.number;
}
