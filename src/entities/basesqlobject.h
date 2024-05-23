#ifndef BASESQLOBJECT_H
#define BASESQLOBJECT_H
#include <QSharedPointer>
#include <exception>
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


class SqlObject {
private:
    int mId;
public:
    SqlObject(const int& id);
    SqlObject(int&& id);
    void set_id(const int& id);
    void set_id(int&& id);
    const int& id() const;
};

//struct wrapper_is_empty : public std::runtime_error {
//public:
//    wrapper_is_empty(const char* Message);
//    wrapper_is_empty(const std::string& Message);
//};

#endif // BASESQLOBJECT_H
