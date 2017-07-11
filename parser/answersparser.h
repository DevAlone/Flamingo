#ifndef ANSWERSPARSER_H
#define ANSWERSPARSER_H

#include "parser.h"

#include <answer.h>

namespace parser {
class AnswersParser : public Parser {
public:
    AnswersParser();

    // function can return empty pointer
    std::shared_ptr<Answer> parseAnswer(
        const QString& string,
        char answerLetter,
        unsigned long baseLineNumber);

private:
    unsigned long baseLineNumber = 0;
    unsigned long lineNumber = 0;
};
}

#endif // ANSWERSPARSER_H
