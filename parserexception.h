#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H

#include <QString>

class ParserException {
public:
    ParserException(const QString& message);

    const QString& getMessage() const;

protected:
    QString message;
};

#endif // PARSEREXCEPTION_H
