#ifndef DATABASEINITIALIZATIONERROR_H
#define DATABASEINITIALIZATIONERROR_H

#include "exception.h"



class DatabaseInitializationError : public Exception
{
public:
    DatabaseInitializationError(const QString& message);
};

#endif // DATABASEINITIALIZATIONERROR_H
