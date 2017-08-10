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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgets/mainwidget.h"

#include <QtWidgets>

#include <memory>

class MainWindowUi;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

    virtual void closeEvent(QCloseEvent* event);

signals:

public slots:

private:
    std::unique_ptr<MainWindowUi> ui;
};

class MainWindowUi {
public:
    MainWindowUi(MainWindow* parent)
    {
        //        mainMenuBar = new QMenuBar(parent);
        //        parent->setMenuBar(mainMenuBar);

        //        menuTestAction = new QAction("test fucking action", parent);

        //        mainMenu = new QMenu("Flamingo fucking menu", parent);
        //        mainMenu->addAction(menuTestAction);
        //        parent->menuBar()->addMenu(mainMenu);

        mainWidget = new MainWidget(parent);
        parent->setCentralWidget(mainWidget);
    }

    //    QMenuBar* mainMenuBar;
    //    QAction* menuTestAction;
    //    QMenu* mainMenu;

    MainWidget* mainWidget;
};

#endif // MAINWINDOW_H
