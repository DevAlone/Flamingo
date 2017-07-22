#ifndef MODELSAVINGERROR_H
#define MODELSAVINGERROR_H

#include "modelsqlerror.h"

#include <QSqlError>
#include <QString>

class ModelSavingError : public ModelSqlError {
public:
    ModelSavingError(const QString& message, const QSqlError& sqlError = QSqlError());
};

#endif // MODELSAVINGERROR_H
