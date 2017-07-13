#ifndef ANSWERCREATINGERROR_H
#define ANSWERCREATINGERROR_H

#include <QString>

class AnswerCreatingError {
public:
    AnswerCreatingError(const QString& message);
    virtual ~AnswerCreatingError() {}

protected:
    QString message;
};

#endif // ANSWERCREATINGERROR_H
