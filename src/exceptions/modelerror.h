#ifndef MODELERROR_H
#define MODELERROR_H

#include "exception.h"

#include <QString>

class ModelError : public Exception {
public:
    ModelError(const QString& message);
};

#endif // MODELERROR_H
