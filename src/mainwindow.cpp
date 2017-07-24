#include "mainwindow.h"

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
