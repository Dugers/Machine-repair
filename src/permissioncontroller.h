#ifndef PERMISSIONCONTROLLER_H
#define PERMISSIONCONTROLLER_H
#include "entities/user.h"
#include "models/db.h"


struct permission_error : public std::runtime_error {
public:
    permission_error(const char* Message);
    permission_error(const std::string& Message);
};


template <UserRole role>
class PermissionController
{
public:
    PermissionController(const int& user_id);
    void confirm();
    void set_user_id(const int& user_id);
    const int& user_id() const noexcept;
private:
    int mUser_id;
};

template <UserRole role>
PermissionController<role>::PermissionController(const int& user_id) : mUser_id{user_id} {}

template <UserRole role>
void PermissionController<role>::confirm() {
    try {
        auto user = db::get_user(mUser_id);
        if (user->role() == role)
            return;
    } catch (std::exception& e) {}
    throw permission_error{"У вас недостаточно прав для этого действия!"};
}

template <UserRole role>
void PermissionController<role>::set_user_id(const int& user_id) {
    mUser_id = user_id;
}

template <UserRole role>
const int& PermissionController<role>::user_id() const noexcept {
    return mUser_id;
}
#endif // PERMISSIONCONTROLLER_H
