#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    //    ui = MainWindowUi::makeUi(this);
    ui = new MainWindowUi(this);

    resize(640, 480);
}

MainWindow::~MainWindow()
{
    delete ui;
}
