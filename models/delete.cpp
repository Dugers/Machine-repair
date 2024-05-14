#include "db.h"
#include <QSqlQuery>

bool db::delete_user(const int& user_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("DELETE FROM users WHERE id = :user_id");
    query.bindValue(":user_id", user_id);
    return query.exec();
}

bool db::clear_tables() {
    QSqlQuery query{db::current_pool()};
    bool ans = true;
    ans &= query.exec("DELETE FROM orders");
    ans &= query.exec("DELETE FROM services_marks");
    ans &= query.exec("DELETE FROM services");
    ans &= query.exec("DELETE FROM machines");
    ans &= query.exec("DELETE FROM machine_marks");
    ans &= query.exec("DELETE FROM machine_types");
    ans &= query.exec("DELETE FROM machine_brands");
    ans &= query.exec("DELETE FROM users");
    return ans;
}

bool db::drop_tables() {
    QSqlQuery query{db::current_pool()};
    bool ans = true;
    ans &= query.exec("DROP TABLE orders");
    ans &= query.exec("DROP TABLE services_marks");
    ans &= query.exec("DROP TABLE services");
    ans &= query.exec("DROP TABLE machines");
    ans &= query.exec("DROP TABLE machine_marks");
    ans &= query.exec("DROP TABLE machine_types");
    ans &= query.exec("DROP TABLE machine_brands");
    ans &= query.exec("DROP TABLE users");
    ans &= query.exec("DROP TYPE user_role");
    return ans;
}
