#include "flamingoapplication.h"

#include <exceptions/exception.h>

#include <QtCore>
#include <QtWidgets>

FlamingoApplication::FlamingoApplication(int& argc, char* argv[])
    : QApplication(argc, argv)
{
}

bool FlamingoApplication::notify(QObject* obj, QEvent* event)
{
    //    return QApplication::notify(obj, event);
    bool result = true;
    try {
        result = QApplication::notify(obj, event);
    } catch (const Exception& ex) {
        QMessageBox::warning(
            nullptr,
            QObject::tr("Exception"),
            QObject::tr("Programm will be closed. Text of error: ") + ex.getMessage());
        exit(EXIT_FAILURE);
    }

    return result;
}
