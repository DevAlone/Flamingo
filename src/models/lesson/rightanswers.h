#ifndef RIGHTANSWERS_H
#define RIGHTANSWERS_H

#include <QtCore>

#include <set>

class RightAnswers {

public:
    static RightAnswers fromString(const QString& _expression);

    const std::set<QChar>& getAnswers() const;
    bool isAnswersRight(std::set<QChar> userAnswers) const;

    QString toString() const;
    QString toHumanString() const;

private:
    enum class EXPRESSION_TYPE {
        AND,
        OR
    };
    EXPRESSION_TYPE type;
    std::set<QChar> answers;
};

#endif // RIGHTANSWERS_H
