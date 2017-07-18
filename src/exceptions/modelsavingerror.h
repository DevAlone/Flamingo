#ifndef MODELSAVINGERROR_H
#define MODELSAVINGERROR_H

#include <QSqlError>
#include <QString>

class ModelSavingError {
public:
    ModelSavingError(const QString& message, const QSqlError& sqlError = QSqlError());

    QString message;
    QSqlError sqlError;
};

#endif // MODELSAVINGERROR_H
