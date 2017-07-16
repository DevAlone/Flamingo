#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"

#include <QtWidgets>

class MainWindowUi;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

signals:

public slots:

private:
    MainWindowUi* ui = nullptr;
};

class MainWindowUi {
public:
    MainWindowUi(MainWindow* parent)
    {
        mainMenuBar = new QMenuBar(parent);
        parent->setMenuBar(mainMenuBar);

        menuTestAction = new QAction("test fucking action", parent);

        mainMenu = new QMenu("Flamingo fucking menu", parent);
        mainMenu->addAction(menuTestAction);
        parent->menuBar()->addMenu(mainMenu);

        mainWidget = new MainWidget(parent);
        parent->setCentralWidget(mainWidget);
    }

    QMenuBar* mainMenuBar;
    QAction* menuTestAction;
    QMenu* mainMenu;

    MainWidget* mainWidget;
};

#endif // MAINWINDOW_H
