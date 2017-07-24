#include "moduleitemsingleview.h"

ModuleItemSingleView::ModuleItemSingleView(QWidget *parent)
    : ModelSingleView(parent)
{
    ui = std::make_unique<ModuleItemSingleViewUi>(this);
}
