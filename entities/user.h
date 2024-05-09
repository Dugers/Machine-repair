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
    static QString hash_password(const QString& password);
};

//class UserSql :
//    public User,
//    public BaseSqlObject
//{
//    UserSql(const int& id, const QString& name, const QString& login, const QString& password, const UserRole& role);
//};

#endif // USER_H
