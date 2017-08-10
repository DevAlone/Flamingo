// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#define ANSWER_H

#include <QString>

#include <QJsonObject>
#include <map>
#include <memory>
#include <vector>

enum class ANSWER_TYPE {
    TEXT,
    HTML,
    IMAGE,
    AUDIO,
    VIDEO,
    MIXED
};

const std::map<QString, ANSWER_TYPE> answerTypesMap = {
    { "text", ANSWER_TYPE::TEXT },
    { "html", ANSWER_TYPE::HTML },
    { "image", ANSWER_TYPE::IMAGE },
    { "audio", ANSWER_TYPE::AUDIO },
    { "video", ANSWER_TYPE::VIDEO },
    { "mixed", ANSWER_TYPE::MIXED },
};

class Answer {

public:
    Answer();
    virtual ~Answer();
    static std::shared_ptr<Answer> createAnswer(std::map<QString, QString>& keyValueMap,
        std::vector<std::pair<QString, QString>>& keyValueVec);

    ANSWER_TYPE getType() const;

    virtual QJsonObject toJsonObject() const;
    static std::shared_ptr<Answer> fromJsonObject(const QJsonObject& obj);

private:
    ANSWER_TYPE type;
};

#endif // ANSWER_H
