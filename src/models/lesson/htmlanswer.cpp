#include "htmlanswer.h"

HtmlAnswer::HtmlAnswer(std::map<QString, QString>& keyValueMap,
    std::vector<std::pair<QString, QString> >& keyValueVec)
    : TextAnswer(keyValueMap, keyValueVec)
{
}
