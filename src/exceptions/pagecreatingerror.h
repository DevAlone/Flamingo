#ifndef PAGECREATINGERROR_H
#define PAGECREATINGERROR_H

#include "exception.h"

#include <QString>

class PageCreatingError : public Exception {
public:
    PageCreatingError(const QString& message);
};

#endif // PAGECREATINGERROR_H
