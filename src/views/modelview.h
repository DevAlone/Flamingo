#ifndef MODELVIEW_H
#define MODELVIEW_H

#include "modeldispatcher.h"

#include <QWidget>

#include <memory>

class ModelView : public QWidget {
    Q_OBJECT
public:
    explicit ModelView(QWidget* parent = nullptr);

    virtual std::shared_ptr<Model> getSelectedModel() = 0;

signals:

public slots:

protected:
    std::unique_ptr<ModelDispatcher> dispatcher;
};

#endif // MODELVIEW_H
