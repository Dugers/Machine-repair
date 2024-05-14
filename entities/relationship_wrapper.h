#ifndef RELATIONSHIP_WRAPPER_H
#define RELATIONSHIP_WRAPPER_H
#include <functional>
#include <QSharedPointer>
#include <exception>


struct initializer_is_empty : public std::runtime_error {
public:
    initializer_is_empty(const char* Message);
    initializer_is_empty(const std::string& Message);
};


template <typename T>
class relationship_wrapper
{
    std::function<T&()> mInitializer;
    QSharedPointer<T> mObject;
public:
    relationship_wrapper() = default;
    relationship_wrapper(const relationship_wrapper&) = default;
    relationship_wrapper(relationship_wrapper&&) = default;
    relationship_wrapper(QSharedPointer<T> specific_object);
    relationship_wrapper(const std::function<T&(QSharedPointer<T>& object)>& initializer);
    relationship_wrapper(const std::function<T&(QSharedPointer<T>& object)>&& initializer);
    T& get() const;
    bool empty();
    void set(const std::function<T&(QSharedPointer<T>& object)>& initializer);
    void set(std::function<T&(QSharedPointer<T>& object)>&& initializer);
    static std::function<T&(QSharedPointer<T>& object)> make_simple_initializer(T specific_object);
    relationship_wrapper& operator=(const relationship_wrapper&) = default;
    relationship_wrapper& operator=(relationship_wrapper&&) = default;
};

template<typename T>
relationship_wrapper<T>::relationship_wrapper(QSharedPointer<T> specific_object) :
    mObject{specific_object},
    mInitializer{make_simple_initializer(*specific_object)}
{}
template<typename T>
relationship_wrapper<T>::relationship_wrapper(const std::function<T&(QSharedPointer<T>& object)>& initializer) :
    mInitializer{initializer} {}
template<typename T>
relationship_wrapper<T>::relationship_wrapper(const std::function<T&(QSharedPointer<T>& object)>&& initializer) :
    mInitializer{std::move(initializer)} {}
template<typename T>
T& relationship_wrapper<T>::get() const {
    if (!mInitializer)
        throw initializer_is_empty{"initializer was not set"};
    return mInitializer();
}
template<typename T>
bool relationship_wrapper<T>::empty() {
    return !mObject && !mInitializer;
}
template<typename T>
void relationship_wrapper<T>::set(const std::function<T&(QSharedPointer<T>& object)>& initializer) {
    mInitializer = initializer;
}
template<typename T>
void relationship_wrapper<T>::set(std::function<T&(QSharedPointer<T>& object)>&& initializer) {
    mInitializer = std::move(initializer);
}

template <typename T>
std::function<T&(QSharedPointer<T>& object)> relationship_wrapper<T>::make_simple_initializer(T specific_object) {
    return [specific_object] (QSharedPointer<T>& object) -> T& {
        if (!object)
            object = QSharedPointer<T>::create(specific_object);
        return *object;
    };
}

#endif // RELATIONSHIP_WRAPPER_H
