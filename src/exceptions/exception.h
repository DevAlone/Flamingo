#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class Exception {
public:
    Exception(const QString& message);
    virtual ~Exception();

    const QString& getMessage() const;

protected:
    QString message;
};

#endif // EXCEPTION_H
