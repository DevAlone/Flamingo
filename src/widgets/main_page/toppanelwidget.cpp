#include "toppanelwidget.h"

TopPanelWidget::TopPanelWidget(QWidget* parent)
    : QFrame(parent)
{
    ui = std::make_unique<TopPanelWidgetUi>(this);
    // TODO: check it
    setFrameShape(QFrame::StyledPanel);
}

void TopPanelWidget::menuButtonClicked()
{
    ui->menu->exec(
        ui->menuButton->mapToGlobal(
            QPoint(0, ui->menuButton->height())));
}
