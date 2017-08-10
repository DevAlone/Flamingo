// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
