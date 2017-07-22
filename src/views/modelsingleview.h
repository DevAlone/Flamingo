#ifndef MODELSINGLEVIEW_H
#define MODELSINGLEVIEW_H

#include "modelview.h"

#include <QWidget>

class ModelSingleView : public ModelView
{
    Q_OBJECT
public:
    explicit ModelSingleView(QWidget *parent = nullptr);

    std::shared_ptr<Model> getModel() const;
    void setModel(const std::shared_ptr<Model> &value);

signals:

public slots:

protected:
    std::shared_ptr<Model> model;
};

#endif // MODELSINGLEVIEW_H
