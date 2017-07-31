#include "helper.h"

#include <QtCore>
#include <QtWidgets>

void clearLayout(QLayout* layout)
{
    QLayoutItem* item;
    while (item = layout->takeAt(0)) {
        if (item->layout()) {
            clearLayout(item->layout());

            delete item->layout();
        }

        delete item->widget();

        delete item;
    }
}
