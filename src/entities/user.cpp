#include "user.h"
#include <QCryptographicHash>
#include <random>
#include "config.h"


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

void User::validate_name(const QString& name) {
    if (name != name.simplified())
        throw std::runtime_error{"the name contains extra spaces"};
    if (name.size() < 6)
        throw std::runtime_error{"the name is too short (need >= 6 chars)"};
    static const QString allowed_characters = "йцукенгшщзфывапролджэячсмитьбюёЙЦУКЕНГШЩЗФЫВАПРОЛДЖЭЯЧСМИТЬБЮqwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ";
    for (auto const& ch : name) {
        if (!allowed_characters.contains(ch))
            throw std::runtime_error{"You can only use letters and spaces"};
    }
}

void User::validate_login(const QString& login) {
    if (login.size() < 6)
        throw std::runtime_error{"the login is too short (need >= 6 chars)"};
    static const QString allowed_characters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_";
    for (auto const& ch : login) {
        if (!allowed_characters.contains(ch))
            throw std::runtime_error{"You can only use Latin letters and underscore"};
    }
}

void User::validate_password(const QString& password) {
    if (password.size() < 6)
        throw std::runtime_error{"the password is too short (need >= 6 chars)"};
}

void User::validate_role(const QString& role) {
    if (role_by_str(role) == UserRole::None)
        throw std::runtime_error{"Unknown role"};
}

void User::validate_role(const UserRole& role) {
    if (role == UserRole::None)
        throw std::runtime_error{"Unknown role"};
}

QString User::generate_password() {
    std::mt19937 random_symbols{std::random_device{}()};
    static const QString symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[]{}|;:,.<>?/";
    QString password;
    for (int i = 0; i < 32; ++i) {
        password.push_back(symbols[random_symbols()%symbols.size()]);
    }
    return password;
}

QVector<QString> User::str_values(bool name, bool login, bool password, bool role) const {
    QVector<QString> values;
    if (name)
        values.push_back(this->name());
    if (login)
        values.push_back(this->login());
    if (password)
        values.push_back(this->password());
    if (role)
        values.push_back(str_by_role(this->role()));
    return values;
}

// ============================== SQL TYPES ==============================

UserSql::UserSql(const QString& name, const QString& login, const QString& password, const UserRole& role, const int& id)
    : User{name, login, password, role}
    , SqlObject{id}
{}

UserSql::UserSql(QString&& name, QString&& login, QString&& password, UserRole&& role, int&& id) noexcept
    : User{std::move(name), std::move(login), std::move(password), std::move(role)}
    , SqlObject{id}
{}

UserSql::UserSql(QString&& name, const QString& login, QString&& password, UserRole&& role, int&& id) noexcept
    : User{std::move(name), login, std::move(password), std::move(role)}
    , SqlObject{id}
{}

