//#include "relationship_wrapper.h"

//template<typename T>
//relationship_wrapper<T>::relationship_wrapper(T specific_object) : mInitializer{make_simple_initializer(specific_object)} {}
//template<typename T>
//relationship_wrapper<T>::relationship_wrapper(const std::function<T&(QSharedPointer<T>& object)>& initializer) : mInitializer{initializer} {}
//template<typename T>
//relationship_wrapper<T>::relationship_wrapper(const std::function<T&(QSharedPointer<T>& object)>&& initializer) : mInitializer{std::move(initializer)} {}
//template<typename T>
//T& relationship_wrapper<T>::get() const {
//    return mInitializer();
//}
//template<typename T>
//void relationship_wrapper<T>::set(const std::function<T&(QSharedPointer<T>& object)>& initializer) {
//    mInitializer = initializer;
//}
//template<typename T>
//void relationship_wrapper<T>::set(std::function<T&(QSharedPointer<T>& object)>&& initializer) {
//    mInitializer = std::move(initializer);
//}

//template <typename T>
//std::function<T&(QSharedPointer<T>& object)> relationship_wrapper<T>::make_simple_initializer(T specific_object) {
//    return [specific_object] (QSharedPointer<T>& object) -> T& {
//        if (!object)
//            object = QSharedPointer<T>::create(specific_object);
//        return *object;
//    };
//}
