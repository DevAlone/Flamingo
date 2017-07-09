#ifndef QUESTIONSPARSER_H
#define QUESTIONSPARSER_H

#include "parser.h"

#include <question.h>

namespace parser {
class QuestionsParser : public Parser {
public:
    QuestionsParser();

    /// function can return empty smart pointer.
    /// Check it before using.
    std::shared_ptr<Question> parseString(const QString& string,
        unsigned questionNumber,
        unsigned long baseLineNumber);

private:
};
}

#endif // QUESTIONSPARSER_H
