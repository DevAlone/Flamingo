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
        QString& string,
        QChar answerLetter,
        unsigned long baseLineNumber,
        QString path);

private:
    unsigned long baseLineNumber = 0;
    unsigned long lineNumber = 0;
    QString line;
    QString path;

    void insertKeyValue(std::map<QString, QString>& keyValueMap,
        std::vector<std::pair<QString, QString> >& keyValueVec,
        std::pair<QString, QString> buffer);
};
}

#endif // ANSWERSPARSER_H
