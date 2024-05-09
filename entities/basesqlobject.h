#ifndef BASESQLOBJECT_H
#define BASESQLOBJECT_H
//#include <QSharedPointer>
//#include <exception>
//#include <functional>

//class BaseSqlObject
//{
//private:
//    int mId;
//public:
//    BaseSqlObject(const int& id);
//    void set_id(const int& id);
//    const int& id() const;
//};

//template <typename T>
//class SqlObject {
//private:
//    int mId;
//    QSharedPointer<const T> mObject;
//public:
//    SqlObject(const int& id, const T& object);
//    SqlObject(const int& id, T&& object);
//    void set(const T& object);
//    void set(T&& object);
//    void set_id(const int& id);
//    void set_id(int&& id);
//    const T& get() const;
//    const int& id() const;
//};

//struct wrapper_is_empty : public std::runtime_error {
//public:
//    wrapper_is_empty(const char* Message);
//    wrapper_is_empty(const std::string& Message);
//};

//template <typename T>
//SqlObject<T>::SqlObject(const int& id, T&& object) : mId{id}, mObject{QSharedPointer<T>::create(std::move(object))} {}


//template <typename T>
//const T& SqlObject<T>::get() const {
//    return *mObject;
//}

#endif // BASESQLOBJECT_H
