#include "basesqlobject.h"
////BaseSqlObject::BaseSqlObject(const int& id) : mId{id} {}

////void BaseSqlObject::set_id(const int& id) {
////    mId = id;
////}
////const int& BaseSqlObject::id() const {
////    return mId;
////}

//wrapper_is_empty::wrapper_is_empty(const char* Message) : std::runtime_error{Message} {}
//wrapper_is_empty::wrapper_is_empty(const std::string& Message) : std::runtime_error{Message} {}

SqlObject::SqlObject(const int& id) :
    mId{id}
{}

SqlObject::SqlObject(int&& id) :
    mId{std::move(id)}
{}


void SqlObject::set_id(const int& id) {
    mId = id;
}

void SqlObject::set_id(int&& id) {
    mId = std::move(id);
}

const int& SqlObject::id() const {
    return mId;
}
