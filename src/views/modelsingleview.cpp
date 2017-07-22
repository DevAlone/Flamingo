#include "modelsingleview.h"

ModelSingleView::ModelSingleView(QWidget* parent)
    : ModelView(parent)
{
}

std::shared_ptr<Model> ModelSingleView::getModel() const
{
    return model;
}

void ModelSingleView::setModel(const std::shared_ptr<Model>& value)
{
    model = value;
}
