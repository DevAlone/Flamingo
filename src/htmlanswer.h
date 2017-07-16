#ifndef HTMLANSWER_H
#define HTMLANSWER_H

#include "textanswer.h"

class HtmlAnswer : public TextAnswer {
public:
    HtmlAnswer(std::map<QString, QString>& keyValueMap,
        std::vector<std::pair<QString, QString>>& keyValueVec);
};

#endif // HTMLANSWER_H
