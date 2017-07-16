#ifndef NULLABLE_H
#define NULLABLE_H

#include <exception>
#include <stdexcept>

template <typename T>
class Nullable final {
public:
    Nullable();
    Nullable(const Nullable<T>& other);
    Nullable<T>& operator=(const Nullable<T>& other);
    Nullable(Nullable<T>&& other);
    Nullable<T>& operator=(Nullable<T>&& other);

    Nullable(const T& value);
    const T& operator=(const T& value);
    operator const T&() const;
    ~Nullable();

    void setValue(const T& val);
    const T& getValue();

    bool isNull() const;
    bool isValid() const;

private:
    T* value = nullptr;
};

#endif // NULLABLE_H

template <typename T>
Nullable<T>::Nullable()
{
}

template <typename T>
Nullable<T>::Nullable(const Nullable<T>& other)
{
    this->value = new T(*other.value);
}

template <typename T>
Nullable<T>& Nullable<T>::operator=(const Nullable<T>& other)
{
    setValue(other);
    return *this;
}

template <typename T>
Nullable<T>::Nullable(Nullable<T>&& other)
{
    this->value = other.value;
    other.value = nullptr;
}

template <typename T>
Nullable<T>& Nullable<T>::operator=(Nullable<T>&& other)
{
    this->value = other.value;
    other.value = nullptr;
    return *this;
}

template <typename T>
Nullable<T>::Nullable(const T& value)
{
    value = new T(value);
}

template <typename T>
const T& Nullable<T>::operator=(const T& value)
{
    setValue(value);
    return getValue();
}

template <typename T>
Nullable<T>::operator const T&() const
{
    return getValue();
}

template <typename T>
Nullable<T>::~Nullable()
{
    delete value;
    value = nullptr;
}

template <typename T>
void Nullable<T>::setValue(const T& val)
{
    delete value;
    value = new T(val);
}

template <typename T>
const T& Nullable<T>::getValue()
{
    if (isNull())
        throw std::runtime_error("Attempting to get null value");
    return *value;
}

template <typename T>
bool Nullable<T>::isNull() const
{
    return value == nullptr;
}

template <typename T>
bool Nullable<T>::isValid() const
{
    return value != nullptr;
}
