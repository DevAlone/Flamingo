#ifndef ANSWERCREATINGERROR_H
#define ANSWERCREATINGERROR_H

#include "exception.h"

#include <QString>

class AnswerCreatingError : public Exception {
public:
    AnswerCreatingError(const QString& message);
};

#endif // ANSWERCREATINGERROR_H
