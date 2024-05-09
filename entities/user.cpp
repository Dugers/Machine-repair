#include "user.h"
#include <QCryptographicHash>
#include "../config.cpp"

User::User(const QString& name, const QString& login, const QString& password, const UserRole& role) :
    mName{name}, mLogin{login}, mPassword{password}, mRole{role} {}

User::User(QString&& name, QString&& login, QString&& password, UserRole&& role) noexcept:
    mName{std::move(name)}, mLogin{std::move(login)}, mPassword{std::move(password)}, mRole{std::move(role)} {}

User::User(QString&& name, const QString& login, QString&& password, UserRole&& role) noexcept:
    mName{std::move(name)}, mLogin{login}, mPassword{std::move(password)}, mRole{std::move(role)} {}

void User::set_name(const QString& name) {
    mName = name;
}

void User::set_name(QString&& name) {
    mName = std::move(name);
}
void User::set_login(const QString& login) {
    mLogin = login;
}
void User::set_login(QString&& login) {
    mLogin = std::move(login);
}
void User::set_password(const QString& password) {
    mPassword = password;
}
void User::set_password(QString&& password) {
    mPassword = std::move(password);
}
void User::set_role(const UserRole& role) {
    mRole = role;
}
void User::set_role(UserRole&& role) {
    mRole = std::move(role);
}

const QString& User::name() const {
    return mName;
}
const QString& User::login() const {
    return mLogin;
}
const QString& User::password() const {
    return mPassword;
}
const UserRole& User::role() const {
    return mRole;
}

QString User::hash_password(const QString& password) {
    return QCryptographicHash::hash((password + config::db::PASSWORD_SALT).toUtf8(), QCryptographicHash::Sha256);
}

UserRole role_by_str(const QString& role) {
    if (role == "Admin") return UserRole::Admin;
    if (role == "Client") return UserRole::Client;
    if (role == "Worker") return UserRole::Worker;
    return UserRole::None;
}

QString str_by_role(const UserRole& role) {
    switch (role) {

    case (UserRole::Admin):
        return "Admin";
    case (UserRole::Client):
        return "Client";
    case (UserRole::Worker):
        return "Worker";
    default:
        return "None";

    }
}

const QVector<QPair<QString, UserRole>>& get_user_roles() {
    static const QVector<QPair<QString, UserRole>> roles = {{"Admin", UserRole::Admin}, {"Worker", UserRole::Worker}, {"Client", UserRole::Client}};
    return roles;
}
