#ifndef PAGECREATINGERROR_H
#define PAGECREATINGERROR_H

#include <QString>

//#include <exception>
//#include <stdexcept>

class PageCreatingError {
public:
    PageCreatingError(const QString& message);

    const QString& getMessage() const;

protected:
    QString message;
};

#endif // PAGECREATINGERROR_H
