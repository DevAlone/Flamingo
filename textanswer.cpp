#include "textanswer.h"

TextAnswer::TextAnswer(std::map<QString, QString> keyValueMap,
    std::vector<std::pair<QString, QString> >& keyValueVec)
{
    auto contentIt = keyValueMap.find("content");
    if (contentIt != keyValueMap.end())
        content = contentIt->second;
}

const QString& TextAnswer::getContent() const
{
    return content;
}
