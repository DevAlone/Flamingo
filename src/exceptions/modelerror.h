#ifndef MODELERROR_H
#define MODELERROR_H

#include <QString>

class ModelError {
public:
    ModelError(const QString& message);

    const QString& getMessage() const;

private:
    QString message;
};

#endif // MODELERROR_H
