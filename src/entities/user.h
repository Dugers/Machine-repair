#ifndef USER_H
#define USER_H
#include <QString>
#include "basesqlobject.h"

enum class UserRole {
  Client,
  Worker,
  Admin,
  None
};

UserRole role_by_str(const QString& role);
QString str_by_role(const UserRole& role);
const QVector<QPair<QString, UserRole>>& get_user_roles();

class User
{
private:
    QString mName;
    QString mLogin;
    QString mPassword;
    UserRole mRole;
public:
    User(const QString& name, const QString& login, const QString& password, const UserRole& role);
    User(QString&& name, QString&& login, QString&& password, UserRole&& role) noexcept;
    User(QString&& name, const QString& login, QString&& password, UserRole&& role) noexcept;
    User(const User&) = default;
    User(User&&) noexcept = default;
    void set_name(const QString& name);
    void set_name(QString&& name);
    void set_login(const QString& login);
    void set_login(QString&& login);
    void set_password(const QString& password);
    void set_password(QString&& password);
    void set_role(const UserRole& role);
    void set_role(UserRole&& role);
    const QString& name() const;
    const QString& login() const;
    const QString& password() const;
    const UserRole& role() const;
    User& operator=(User&) = default;
    User& operator=(User&&) noexcept = default;
    QVector<QString> str_values(bool name = true, bool login = true, bool password = false, bool role = true) const;
    void validate_name();
    void validate_login();
    void validate_password();
    void validate_role();
    static QString hash_password(const QString& password);
    static void validate_name(const QString& name);
    static void validate_login(const QString& login);
    static void validate_password(const QString& password);
    static void validate_role(const QString& role);
    static void validate_role(const UserRole& role);
    static QString generate_password();
};

class UserSql :
    public User,
    public SqlObject
{
public:
    UserSql(const QString& name, const QString& login, const QString& password, const UserRole& role, const int& id);
    UserSql(QString&& name, QString&& login, QString&& password, UserRole&& role, int&& id) noexcept;
    UserSql(QString&& name, const QString& login, QString&& password, UserRole&& role, int&& id) noexcept;
};

#endif // USER_H
