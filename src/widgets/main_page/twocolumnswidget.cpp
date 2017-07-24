#include "twocolumnswidget.h"

TwoColumnsWidget::TwoColumnsWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<TwoColumnsWidgetUi>(this);
    setLeftFixedSize(300);
}

void TwoColumnsWidget::addLeftWidget(QWidget* widget)
{
    ui->leftColumnLayout->addWidget(widget);
}

void TwoColumnsWidget::addRightWidget(QWidget* widget)
{
    ui->rightColumnLayout->addWidget(widget);
}

void TwoColumnsWidget::addLeftLayout(QLayout* layout)
{
    ui->leftColumnLayout->addLayout(layout);
}

void TwoColumnsWidget::addRightLayout(QLayout* layout)
{
    ui->rightColumnLayout->addLayout(layout);
}

void TwoColumnsWidget::setLeftFixedSize(unsigned int px)
{
    ui->leftColumnWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum));
    ui->leftColumnWidget->setMinimumWidth(px);
    ui->leftColumnWidget->setMaximumHeight(10000000);
}
