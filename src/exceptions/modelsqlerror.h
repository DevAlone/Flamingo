#ifndef MODELSQLERROR_H
#define MODELSQLERROR_H

#include "modelerror.h"

#include <QSqlError>

class ModelSqlError : public ModelError {
public:
    ModelSqlError(const QString& message, const QSqlError& sqlError);

    QSqlError sqlError;
};

#endif // MODELSQLERROR_H
