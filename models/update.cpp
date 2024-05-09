#include "db.h"
#include <QSqlQuery>
#include "../entities/user.h"

bool db::update_user_name(const QSqlDatabase& db, const int& user_id, const QString& new_name) {
    QSqlQuery query{db};
    query.prepare("UPDATE users SET name = :new_name WHERE id = :user_id");
    query.bindValue(":new_name", new_name);
    query.bindValue(":user_id", user_id);
    return query.exec();
}

bool db::update_user_login(const QSqlDatabase& db, const int& user_id, const QString& new_login) {
    QSqlQuery query{db};
    query.prepare("UPDATE users SET login = :new_login WHERE id = :user_id");
    query.bindValue(":new_login", new_login);
    query.bindValue(":user_id", user_id);
    return query.exec();
}

bool db::update_user_role(const QSqlDatabase& db, const int& user_id, const UserRole& new_role) {
    QSqlQuery query{db};
    query.prepare("UPDATE users SET role = :new_role WHERE id = :user_id");
    query.bindValue(":new_role", str_by_role(new_role));
    query.bindValue(":user_id", user_id);
    return query.exec();
}

bool db::update_user_password(const QSqlDatabase& db, const int& user_id, const QString& new_password) {
    QSqlQuery query{db};
    query.prepare("UPDATE users SET password = :new_password WHERE id = :user_id");
    query.bindValue(":new_password", User::hash_password(new_password));
    query.bindValue(":user_id", user_id);
    return query.exec();
}

bool db::update_order_executor(const QSqlDatabase& db, const int& order_id, const int& new_executor_id) {
    QSqlQuery query{db};
    query.prepare("UPDATE orders SET executor = :new_executor_id WHERE id = :order_id");
    query.bindValue(":new_executor_id", new_executor_id);
    query.bindValue(":order_id", order_id);
    return query.exec();
}

bool db::complete_order(const QSqlDatabase& db, const int& order_id, const QString& description) {
    QSqlQuery query{db};
    query.prepare("UPDATE orders SET complete = true, date_end = NOW(), description = :description WHERE id = :order_id");
    query.bindValue(":description", description);
    query.bindValue(":order_id", order_id);
    return query.exec();
}
