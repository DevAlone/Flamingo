#include "pagecreatingerror.h"

PageCreatingError::PageCreatingError(const QString& message)
    : Exception(message)
{
}
