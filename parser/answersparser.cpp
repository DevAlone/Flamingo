#include "answersparser.h"

namespace parser {
AnswersParser::AnswersParser()
{
}

std::shared_ptr<Answer> AnswersParser::parseAnswer(const QString& string, char answerLetter, unsigned long baseLineNumber)
{
    this->baseLineNumber = baseLineNumber;
    lineNumber = 0;

    // parse and create fucking answer

    // TODO: call fabric method
    return std::shared_ptr<Answer>();
}
}
