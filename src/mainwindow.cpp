#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    //    ui = MainWindowUi::makeUi(this);
    ui = std::make_unique<MainWindowUi>(this);

    //    resize(640, 480);
}

MainWindow::~MainWindow()
{
}
