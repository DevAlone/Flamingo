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



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    //    ui = MainWindowUi::makeUi(this);
    ui = std::make_unique<MainWindowUi>(this);

    resize(640, 480);

    QSettings s;

    QVariant geometry = s.value("geometry");
    if (geometry.isValid())
        restoreGeometry(geometry.toByteArray());

    QVariant state = s.value("windowState");
    if (state.isValid())
        restoreState(state.toByteArray());
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings;

    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}
