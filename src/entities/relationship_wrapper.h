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
    relationship_wrapper(QSharedPointer<T> specific_object) :
        mObject{specific_object},
        mInitializer{make_simple_initializer(*specific_object)}
    {}
    relationship_wrapper(const std::function<T&(QSharedPointer<T>& object)>& initializer) :
        mInitializer{initializer}
    {}
    relationship_wrapper(const std::function<T&(QSharedPointer<T>& object)>&& initializer) :
        mInitializer{std::move(initializer)}
    {}
    T& get() const {
        if (!mInitializer) {
            if (mObject)
                return *mObject;
            throw initializer_is_empty{"initializer was not set"};
        }
        return mInitializer(mObject);
    }

    bool empty() const noexcept {
        return !mObject && !mInitializer;
    }
    void set(const std::function<T&(QSharedPointer<T>& object)>& initializer) {
        mInitializer = initializer;
    }
    void set(std::function<T&(QSharedPointer<T>& object)>&& initializer) {
        mInitializer = std::move(initializer);
    }
    explicit operator bool() const noexcept {
        return !empty();
    }
    bool operator !() const noexcept {
        return empty(); }
    T& operator*() const {
        return get();
    }
    T* operator->() const noexcept {
        return &get();
    }
    relationship_wrapper& operator=(const relationship_wrapper&) = default;
    relationship_wrapper& operator=(relationship_wrapper&&) = default;
    static std::function<T&(QSharedPointer<T>& object)> make_simple_initializer(T specific_object);
};

template <typename T>
std::function<T&(QSharedPointer<T>& object)> relationship_wrapper<T>::make_simple_initializer(T specific_object) {
    return [specific_object] (QSharedPointer<T>& object) -> T& {
        if (!object)
            object = QSharedPointer<T>::create(specific_object);
        return *object;
    };
}

#endif // RELATIONSHIP_WRAPPER_H
