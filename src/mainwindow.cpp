#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    //    ui = MainWindowUi::makeUi(this);
    ui = new MainWindowUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
