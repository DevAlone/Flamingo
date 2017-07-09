#include "questionsparser.h"
#include "logger/questionsparserlogentry.h"

namespace parser {
QuestionsParser::QuestionsParser()
{
}

std::shared_ptr<Question> QuestionsParser::parseString(const QString& string, unsigned questionNumber, unsigned long baseLineNumber)
{

    // TODO: change questions parser log entry
    //    logEntry<QuestionsParserLogEntry>(
    //        LOG_ENTRY_TYPE::DEBUG,
    //        QObject::tr("Start parsing of question number ")
    //            + QString::number(questionNumber)
    //            + QObject::tr(" from buffer"),
    //        path);

    // TODO: parse Question

    return std::shared_ptr<Question>();
}
}
