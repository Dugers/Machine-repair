#include "db.h"
#include <QSqlQuery>
#include <QSqlRecord>

void db::create_tables() {
    db::create_enum_roles();
    db::create_table_users();
    db::create_table_machine_types();
    db::create_table_machine_brands();
    db::create_table_machine_marks();
    db::create_table_machines();
    db::create_table_services();
    db::create_table_services_marks();
    db::create_table_orders();
}

void db::create_enum_roles() {
    QSqlQuery select_query{db::current_pool()};
    select_query.prepare("SELECT * FROM pg_type WHERE typname = :typeName");
    select_query.bindValue(":typeName", "user_role"); // Проверяем существует ли такой тип

    if (!select_query.exec()) // Выполнился ли запрос
        throw std::runtime_error{"Failed to make select request"};

    if (!select_query.next()) { // Тип еще не создан, значит создаем
        QSqlQuery create_query{db::current_pool()};
        if (!create_query.exec("CREATE TYPE user_role AS ENUM ('Client', 'Worker', 'Admin')")) // Выполнился ли запрос
            throw std::runtime_error{"Failed to create enum user_role request"};

    }
}

void db::create_table_users() {
    QSqlQuery create_query{db::current_pool()};
    bool success = create_query.exec(R"!!!(
    CREATE TABLE IF NOT EXISTS users (
        id SERIAL PRIMARY KEY NOT NULL,
        name TEXT NOT NULL,
        login TEXT UNIQUE NOT NULL,
        password TEXT NOT NULL,
        role user_role NOT NULL
    )
)!!!");
    if (!success)
        throw std::runtime_error{"Failed to create users table request"};
}

void db::create_table_machine_types() {
    QSqlQuery create_query{db::current_pool()};
    bool success = create_query.exec(R"!!!(
    CREATE TABLE IF NOT EXISTS machine_types (
        id SERIAL PRIMARY KEY NOT NULL,
        name TEXT UNIQUE NOT NULL
    )
)!!!");

    if (!success)
        throw std::runtime_error{"Failed to create machine_types table request"};
}

void db::create_table_machine_brands() {
    QSqlQuery create_query{db::current_pool()};
    bool success = create_query.exec(R"!!!(
    CREATE TABLE IF NOT EXISTS machine_brands (
      id SERIAL PRIMARY KEY NOT NULL,
      name TEXT UNIQUE NOT NULL
    )
)!!!");

    if (!success)
        throw std::runtime_error{"Failed to create machine_brands table request"};
}

void db::create_table_machine_marks() {
    QSqlQuery create_query{db::current_pool()};
    bool success = create_query.exec(R"!!!(
    CREATE TABLE IF NOT EXISTS machine_marks (
        id SERIAL PRIMARY KEY NOT NULL,
        type INTEGER REFERENCES machine_types(id) NOT NULL,
        brand INTEGER REFERENCES machine_brands(id) NOT NULL,
        UNIQUE(type, brand)
    )
)!!!");

    if (!success)
        throw std::runtime_error{"Failed to create machine_marks table request"};

}

void db::create_table_machines() {
    QSqlQuery create_query{db::current_pool()};
    bool success = create_query.exec(R"!!!(
    CREATE TABLE IF NOT EXISTS machines (
        id SERIAL PRIMARY KEY NOT NULL,
        name TEXT NOT NULL,
        owner INTEGER REFERENCES users(id) NOT NULL,
        mark INTEGER REFERENCES machine_marks(id) NOT NULL,
        UNIQUE(owner, name)
    )
)!!!");

    if (!success)
        throw std::runtime_error{"Failed to create machines table request"};
}

void db::create_table_services() {
    QSqlQuery create_query{db::current_pool()};
    bool success = create_query.exec(R"!!!(
    CREATE TABLE IF NOT EXISTS services (
        id SERIAL PRIMARY KEY NOT NULL,
        name TEXT UNIQUE NOT NULL,
        duration_months smallint NOT NULL DEFAULT 0,
        duration_days smallint NOT NULL DEFAULT 0,
        duration_hours smallint NOT NULL DEFAULT 0,
        duration_minutes smallint NOT NULL DEFAULT 0,
        price decimal(9, 2) NOT NULL
    )
)!!!");

    if (!success)
        throw std::runtime_error{"Failed to create services table request"};
}

void db::create_table_services_marks() {
    QSqlQuery create_query{db::current_pool()};
    bool success = create_query.exec(R"!!!(
    CREATE TABLE IF NOT EXISTS services_marks (
        id SERIAL PRIMARY KEY NOT NULL,
        service INTEGER REFERENCES services(id) NOT NULL,
        mark INTEGER REFERENCES machine_marks(id) NOT NULL,
        duration_months smallint,
        duration_days smallint,
        duration_hours smallint,
        duration_minutes smallint,
        price decimal(9, 2),
        UNIQUE(service, mark)
    )
)!!!");

    if (!success)
        throw std::runtime_error{"Failed to create users table request"};
}

void db::create_table_orders() {
    QSqlQuery create_query{db::current_pool()};
    bool success = create_query.exec(R"!!!(
    CREATE TABLE IF NOT EXISTS orders (
        id SERIAL PRIMARY KEY NOT NULL,
        date_start DATE NOT NULL DEFAULT CURRENT_DATE,
        date_end DATE DEFAULT NULL,
        complete BOOLEAN NOT NULL DEFAULT false,
        description TEXT DEFAULT NULL,
        customer INTEGER REFERENCES users(id) NOT NULL,
        executor INTEGER REFERENCES users(id) DEFAULT NULL,
        machine INTEGER REFERENCES machines(id) NOT NULL,
        service INTEGER REFERENCES services(id) NOT NULL
    )
)!!!");
    if (success)
        success = create_query.exec(R"!!!(
        CREATE UNIQUE INDEX IF NOT EXISTS orders_unique_index
            ON orders (customer, machine, service)
            WHERE complete = FALSE;
)!!!");

    if (!success)
        throw std::runtime_error{"Failed to create orders table request"};
}


bool db::create_order(const int& customer_id, const int& machine_id, const int& service_id, const QDate& date_start) {
    QSqlQuery query{db::current_pool()};
    query.prepare("INSERT INTO orders(date_start, customer, machine, service) "
                              "VALUES(:date_start, :customer, :machine, :service)");
    query.bindValue(":date_start", date_start);
    query.bindValue(":customer", customer_id);
    query.bindValue(":machine", machine_id);
    query.bindValue(":service", service_id);
    return query.exec();
}

bool db::create_machine(const Machine& machine, const int& owner_id, const int& mark_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("INSERT INTO machines(name, owner, mark) "
                              "VALUES(:name, :owner, :mark)");
    query.bindValue(":name", machine.name());
    query.bindValue(":owner", owner_id);
    query.bindValue(":mark", mark_id);
    return query.exec();
}

bool db::create_user(const User& user) {
    QSqlQuery query{db::current_pool()};
    query.prepare("INSERT INTO users(name, login, password, role) "
                              "VALUES(:name, :login, :password, :role)");
    query.bindValue(":name", user.name());
    query.bindValue(":login", user.login());
    query.bindValue(":password", User::hash_password(user.password()));
    query.bindValue(":role", str_by_role(user.role()));
    return query.exec();
}

bool db::create_machine_mark(const int& type_id, const int& brand_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("INSERT INTO machine_marks(type, brand) "
                              "VALUES(:type, :brand)");
    query.bindValue(":type", type_id);
    query.bindValue(":brand", brand_id);
    return query.exec();
}
