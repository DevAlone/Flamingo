#include "pagecreatingerror.h"

PageCreatingError::PageCreatingError(const QString& message)
    : message(message)
{
}

const QString& PageCreatingError::getMessage() const
{
    return message;
}
