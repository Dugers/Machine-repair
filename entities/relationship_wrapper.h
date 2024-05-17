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
class relationship_wrapper {
private:
    mutable QSharedPointer<T> mObject;
    std::function<void(QSharedPointer<T>&)> mInitializer;

public:
    relationship_wrapper() = default;
    relationship_wrapper(const relationship_wrapper&) = default;
    relationship_wrapper(relationship_wrapper&&) noexcept = default;
    template <typename U>
    relationship_wrapper(QSharedPointer<U>& object) : mObject{object} {}
    relationship_wrapper(std::function<void(QSharedPointer<T>&)> initializer) : mInitializer(initializer) {}

    relationship_wrapper& operator=(const relationship_wrapper&) = default;
    relationship_wrapper& operator=(relationship_wrapper&&) = default;

    const T& get() const {
        if (!mObject) {
            if (mInitializer)
                mInitializer(mObject);
            else
                throw initializer_is_empty{"initializer was not set"};
        }
        return *mObject;
    }

    bool empty() const noexcept { return !mObject; }
    explicit operator bool() const noexcept { return !empty(); }
    bool operator !() const noexcept { return empty(); }
    const T& operator*() const { return get(); }
    const T* operator->() const { return &get(); }
//    static std::function<void(QSharedPointer<T>&)> make_simple_initializer(const T& specific_object);
};

//template <typename T>
//std::function<void(QSharedPointer<T>&)> relationship_wrapper<T>::make_simple_initializer(const T& specific_object) {
//    return [specific_object](QSharedPointer<T>& ptr) {
//        try {
//        if (!ptr)
//            ptr = QSharedPointer<T>::create(specific_object);
//        }
//        catch (std::exception) {
//            throw std::runtime_error{"Все плохо"};
//        }
//    };
//}


#endif // RELATIONSHIP_WRAPPER_H
