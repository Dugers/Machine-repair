#include "db.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "../config.h"

int db::get_client_orders_count(const int& user_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT COUNT(*) AS count_orders FROM orders WHERE customer = :user_id");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select user's orders count"};
    query.next();
    return query.value("count_orders").toInt();
}

int db::get_worker_orders_count(const int& user_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT COUNT(*) AS count_orders FROM orders WHERE executor = :user_id AND complete = false");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select user's orders count"};
    query.next();
    return query.value("count_orders").toInt();
}

QSharedPointer<QDate> db::get_last_repair_date(const int& machine_id){
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT date_end FROM orders WHERE machine = :machine_id AND complete = true ORDER BY date_end DESC LIMIT 1");
    query.bindValue(":machine_id", machine_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select machine's date of last repair"};
    if (!query.next())
        return {};
    return QSharedPointer<QDate>::create(query.value("date_end").toDate());
}

QSharedPointer<UserSql> db::get_user(const QString& user_login) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM users WHERE login = :login");
    query.bindValue(":login", user_login);
    if (!query.exec())
        throw std::runtime_error{"Failed to select user request"};
    if (!query.next())
        return {};
    QString password = query.value("password").toString();
    UserRole role = role_by_str(query.value("role").toString());
    QString name = query.value("name").toString();
    int id = query.value("id").toInt();
    return QSharedPointer<UserSql>::create(std::move(name), user_login, std::move(password), std::move(role), id);
}

QSharedPointer<UserSql> db::get_user(const int& user_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", user_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select user request"};
    if (!query.next())
        return {};
    QString login = query.value(query.record().indexOf("login")).toString();
    QString password = query.value(query.record().indexOf("password")).toString();
    UserRole role = role_by_str(query.value(query.record().indexOf("role")).toString());
    QString name = query.value(query.record().indexOf("name")).toString();
    return QSharedPointer<UserSql>::create(std::move(name), std::move(login), std::move(password), std::move(role), user_id);
}

QSharedPointer<MachineMark::MachineBrandSql> db::get_machine_brand(const int& brand_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM machine_brands WHERE id = :id");
    query.bindValue(":id", brand_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select mark request"};
    if (!query.next())
        return {};
    QString name = query.value(query.record().indexOf("name")).toString();
    return QSharedPointer<MachineMark::MachineBrandSql>::create(std::move(name), brand_id);
}

QSharedPointer<MachineMark::MachineTypeSql> db::get_machine_type(const int& type_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM machine_types WHERE id = :id");
    query.bindValue(":id", type_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select mark request"};
    if (!query.next())
        return {};
    QString name = query.value(query.record().indexOf("name")).toString();
    return QSharedPointer<MachineMark::MachineTypeSql>::create(std::move(name), type_id);
}

QSharedPointer<MachineMarkSql> db::get_machine_mark(const int& mark_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM machine_marks WHERE id = :id");
    query.bindValue(":id", mark_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select mark request"};
    if (!query.next())
        return {};
    int brand_id = query.value(query.record().indexOf("brand")).toInt();
    int type_id = query.value(query.record().indexOf("type")).toInt();
    return QSharedPointer<MachineMarkSql>::create(std::move(*get_machine_type(type_id)), std::move(*get_machine_brand(brand_id)), mark_id);
}

QSharedPointer<MachineMarkSql> db::get_machine_mark(const int& type_id, const int& brand_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM machine_marks WHERE brand = :brand AND type = :type");
    query.bindValue(":brand", brand_id);
    query.bindValue(":type", type_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select mark request"};
    if (!query.next())
        return {};
    int mark_id = query.value(query.record().indexOf("id")).toInt();
    return QSharedPointer<MachineMarkSql>::create(std::move(*get_machine_type(type_id)), std::move(*get_machine_brand(brand_id)), mark_id);
}

QSharedPointer<MachineSql> db::get_machine(const int& machine_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM machines WHERE id = :machine_id");
    query.bindValue(":machine_id", machine_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select machine request"};
    if (!query.next())
        return {};
    int owner_id = query.value(query.record().indexOf("owner")).toInt();
    QSharedPointer<UserSql> owner = db::get_user(owner_id);
    QString name = query.value(query.record().indexOf("name")).toString();
    QSharedPointer<MachineMarkSql> mark = db::get_machine_mark(query.value(query.record().indexOf("mark")).toInt());
    return QSharedPointer<MachineSql>::create(std::move(name), owner, mark, machine_id);
}

QSharedPointer<MachineSql> db::get_machine_by_order(const int& order_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT machine FROM orders WHERE id = :order_id");
    query.bindValue(":order_id", order_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select machine request"};
    if (!query.next())
        return {};
    return db::get_machine(query.value("machine").toInt());
}

QSharedPointer<ServiceSql> db::get_service(const int& machine_id, const int& service_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare(R"!!!(
    SELECT
        services.id AS id,
        services.name AS name,
        COALESCE(services_marks.duration_months, services.duration_months) as duration_months,
        COALESCE(services_marks.duration_days, services.duration_days) as duration_days,
        COALESCE(services_marks.duration_hours, services.duration_hours) as duration_hours,
        COALESCE(services_marks.duration_minutes, services.duration_minutes) as duration_minutes,
        COALESCE(services_marks.price, services.price) as price
    FROM services
    INNER JOIN services_marks ON services.id = services_marks.service
    WHERE services_marks.mark = (SELECT mark FROM machines WHERE machines.id = :machine_id) AND services_marks.service = :service_id
)!!!");
    query.bindValue(":machine_id", machine_id);
    query.bindValue(":service_id", service_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select service request"};
    if (!query.next())
        return {};
    QString name = query.value(query.record().indexOf("name")).toString();
    unsigned int duration_months = query.value("duration_months").toUInt();
    unsigned int duration_days = query.value("duration_days").toUInt();
    unsigned int duration_hours = query.value("duration_hours").toUInt();
    unsigned int duration_minutes = query.value("duration_minutes").toUInt();
    Duration duration{duration_months, duration_days, duration_hours, duration_minutes};
    double price = query.value("price").toDouble();
    return QSharedPointer<ServiceSql>::create(std::move(name), std::move(duration), std::move(price), service_id);

}

QSharedPointer<OrderSql> db::get_order(const int& order_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM orders WHERE id = :order_id");
    query.bindValue(":order_id", order_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select order request"};
    if (!query.next())
        return {};
    QSharedPointer<User> customer = get_user(query.value("customer").toInt());
    QSharedPointer<Service> service = get_service(query.value("machine").toInt(), query.value("service").toInt());
    QSharedPointer<Machine> machine = get_machine(query.value("machine").toInt());
    QDate date_start = query.value("date_start").toDate();
    Order order{date_start, customer, machine, service};
    if (query.value("complete").toBool()) {
        order.set_complete(true);
        order.set_date_end(query.value("date_end").toDate());
        order.set_description(query.value("description").toString());
    }
    if (!query.isNull("executor"))
        order.set_executor(get_user(query.value("executor").toInt()));
    return QSharedPointer<OrderSql>::create(std::move(order), order_id);
}

QVector<MachineSql> db::get_machines(const int& owner_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare("SELECT * FROM machines WHERE owner = :owner_id");
    query.bindValue(":owner_id", owner_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select machines request"};
    QVector<MachineSql> machines;
    QSharedPointer<UserSql> owner = db::get_user(owner_id);
    while (query.next()) {
        int machine_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        QSharedPointer<MachineMarkSql> mark = db::get_machine_mark(query.value(query.record().indexOf("mark")).toInt());
        machines.push_back({std::move(name), std::move(owner), std::move(mark), machine_id});
    }
    return machines;
}

QVector<ServiceSql> db::get_services(const int& machine_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare(R"!!!(
    SELECT
        services.id AS id,
        services.name AS name,
        COALESCE(services_marks.duration_months, services.duration_months) as duration_months,
        COALESCE(services_marks.duration_days, services.duration_days) as duration_days,
        COALESCE(services_marks.duration_hours, services.duration_hours) as duration_hours,
        COALESCE(services_marks.duration_minutes, services.duration_minutes) as duration_minutes,
        COALESCE(services_marks.price, services.price) as price
    FROM services
    INNER JOIN services_marks ON services.id = services_marks.service
    WHERE services_marks.mark = (SELECT mark FROM machines WHERE machines.id = :machine_id)
)!!!");
    query.bindValue(":machine_id", machine_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select services request"};
    QVector<ServiceSql> services;
    while (query.next()) {
        int service_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        unsigned int duration_months = query.value("duration_months").toUInt();
        unsigned int duration_days = query.value("duration_days").toUInt();
        unsigned int duration_hours = query.value("duration_hours").toUInt();
        unsigned int duration_minutes = query.value("duration_minutes").toUInt();
        Duration duration{duration_months, duration_days, duration_hours, duration_minutes};
        double price = query.value("price").toDouble();
        services.push_back({std::move(name), std::move(duration), std::move(price), service_id});
    }
    return services;
}

QVector<MachineMark::MachineTypeSql> db::get_machine_types() {
    QSqlQuery query{db::current_pool()};
    if (!query.exec("SELECT * FROM machine_types"))
        throw std::runtime_error{"Failed to select services request"};
    QVector<MachineMark::MachineTypeSql> types;
    while (query.next()) {
        int type_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        types.push_back({std::move(name), type_id});
    }
    return types;
}

QVector<MachineMark::MachineBrandSql> db::get_machine_brands(const int& type_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare(R"!!!(
    SELECT machine_brands.id AS id, machine_brands.name
        FROM machine_marks
        JOIN machine_brands ON machine_marks.brand = machine_brands.id
        WHERE machine_marks.type = :type_id
)!!!");
    query.bindValue(":type_id", type_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select brands request"};
    QVector<MachineMark::MachineBrandSql> brands;
    while (query.next()) {
        int brand_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        brands.push_back({std::move(name), brand_id});
    }
    return brands;
}

QVector<UserSql> db::get_users() {
    QSqlQuery query{db::current_pool()};
    query.prepare(R"!!!(
    SELECT * FROM users;
)!!!");
    if (!query.exec())
        throw std::runtime_error{"Failed to select users request"};
    QVector<UserSql> users;
    while (query.next()) {
        int user_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        QString login = query.value("login").toString();
        QString password = query.value("password").toString();
        UserRole role = role_by_str(query.value("role").toString());
        users.push_back({std::move(name), std::move(login), std::move(password), std::move(role), user_id});
    }
    return users;
}

QVector<OrderSql> db::get_aviable_orders() {
    QSqlQuery query{db::current_pool()};
    if (!query.exec(R"!!!(
                    SELECT id, customer, machine, service, date_start
                    FROM orders
                    WHERE executor is NULL AND complete = false;
            )!!!"))
        throw std::runtime_error{"Failed to select aviable orders request"};
    QVector<OrderSql> orders;
    while (query.next()) {
        int order_id = query.value("id").toInt();
        QSharedPointer<User> customer = get_user(query.value("customer").toInt());
        QSharedPointer<Service> service = get_service(query.value("machine").toInt(), query.value("service").toInt());
        QSharedPointer<Machine> machine = get_machine(query.value("machine").toInt());
        QDate date_start = query.value("date_start").toDate();
        orders.push_back({date_start, customer, machine, service, order_id});
    }
    return orders;
}

QVector<OrderSql> db::get_active_orders(const int& user_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare(R"!!!(
                    SELECT id, customer, machine, service, date_start
                    FROM orders
                    WHERE executor = :user_id AND complete = false;
            )!!!");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select active orders"};
    QVector<OrderSql> orders;
    while (query.next()) {
        int order_id = query.value("id").toInt();
        QSharedPointer<User> customer = get_user(query.value("customer").toInt());
        QSharedPointer<Service> service = get_service(query.value("machine").toInt(), query.value("service").toInt());
        QSharedPointer<Machine> machine = get_machine(query.value("machine").toInt());
        QDate date_start = query.value("date_start").toDate();
        orders.push_back({date_start, customer, machine, service, order_id});
    }
    return orders;
}

QVector<OrderSql> db::get_machine_orders(const int& machine_id) {
    QSqlQuery query{db::current_pool()};
    query.prepare(R"!!!(
                    SELECT *
                    FROM orders
                    WHERE machine = :machine_id;
            )!!!");
    query.bindValue(":machine_id", machine_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select active orders"};
    QVector<OrderSql> orders;
    while (query.next()) {
        int order_id = query.value("id").toInt();
        orders.push_back(*db::get_order(order_id));
    }
    return orders;
}
