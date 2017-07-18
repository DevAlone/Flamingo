#ifndef MODEL_H
#define MODEL_H

class Model {
public:
    Model();
    virtual ~Model();

    virtual void save() = 0;
    int getId() const;

protected:
    int id = -1;
};

#endif // MODEL_H
