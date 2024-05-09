//#include "basesqlobject.h"
////BaseSqlObject::BaseSqlObject(const int& id) : mId{id} {}

////void BaseSqlObject::set_id(const int& id) {
////    mId = id;
////}
////const int& BaseSqlObject::id() const {
////    return mId;
////}

//template <typename T>
//SqlObject<T>::SqlObject(const int& id, const T& object) : mId{id}, mObject{QSharedPointer<T>::create(object)} {}
////template <typename T>
////SqlObject<T>::SqlObject() : mId{0}, mObject{} {}
////template <typename T>
////SqlObject<T>::SqlObject(const int& id, T&& object) : mId{id}, mObject{QSharedPointer<T>::create(std::move(object))} {}
////template <typename T>
////const T& SqlObject<T>::get() const {
////    if (!mObject)
////        throw wrapper_is_empty{"First initialize the object"};
////    return *mObject;
////}
//template <typename T>
//void SqlObject<T>::set(const T& object) {
//    mObject = QSharedPointer<T>::create(object);
//}
//template <typename T>
//void SqlObject<T>::set(T&& object) {
//    mObject = QSharedPointer<T>::create(std::move(object));
//}
//template <typename T>
//void SqlObject<T>::set_id(const int& id) {
//    mId = id;
//}
//template <typename T>
//void SqlObject<T>::set_id(int&& id) {
//    mId = std::move(id);
//}
//template <typename T>
//const int& SqlObject<T>::id() const {
//    return mId;
//}

//wrapper_is_empty::wrapper_is_empty(const char* Message) : std::runtime_error{Message} {}
//wrapper_is_empty::wrapper_is_empty(const std::string& Message) : std::runtime_error{Message} {}
