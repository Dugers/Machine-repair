#include "db.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "../config.cpp"

int db::get_client_orders_count(const QSqlDatabase& db, const int& user_id) {
    QSqlQuery query{db};
    query.prepare("SELECT COUNT(*) AS count_orders FROM orders WHERE customer = :user_id");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select user's orders count"};
    query.next();
    return query.value("count_orders").toInt();
}

int db::get_worker_orders_count(const QSqlDatabase& db, const int& user_id) {
    QSqlQuery query{db};
    query.prepare("SELECT COUNT(*) AS count_orders FROM orders WHERE executor = :user_id AND complete = false");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select user's orders count"};
    query.next();
    return query.value("count_orders").toInt();
}

QSharedPointer<QDate> db::get_last_repair_date(const QSqlDatabase& db, const int& machine_id){
    QSqlQuery query{db};
    query.prepare("SELECT date_end FROM orders WHERE machine = :machine_id AND complete = true ORDER BY date_end DESC LIMIT 1");
    query.bindValue(":machine_id", machine_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select machine's date of last repair"};
    if (!query.next())
        return {};
    return QSharedPointer<QDate>::create(query.value("date_end").toDate());
}

QSharedPointer<QPair<int, User>> db::get_user(const QSqlDatabase& db, const QString& user_login) {
    QSqlQuery query{db};
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
    return QSharedPointer<QPair<int, User>>::create(id, User{std::move(name), user_login, std::move(password), std::move(role)});
}

QSharedPointer<QPair<int, User>> db::get_user(const QSqlDatabase& db, const int& user_id) {
    QSqlQuery query{db};
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
    return QSharedPointer<QPair<int, User>>::create(user_id, User{std::move(name), std::move(login), std::move(password), std::move(role)});
}

QSharedPointer<QPair<int, MachineMark::MachineBrand>> db::get_machine_brand(const QSqlDatabase& db, const int& brand_id) {
    QSqlQuery query{db};
    query.prepare("SELECT * FROM machine_brands WHERE id = :id");
    query.bindValue(":id", brand_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select mark request"};
    if (!query.next())
        return {};
    QString name = query.value(query.record().indexOf("name")).toString();
    return QSharedPointer<QPair<int, MachineMark::MachineBrand>>::create(brand_id, MachineMark::MachineBrand{std::move(name)});
}

QSharedPointer<QPair<int, MachineMark::MachineType>> db::get_machine_type(const QSqlDatabase& db, const int& type_id) {
    QSqlQuery query{db};
    query.prepare("SELECT * FROM machine_types WHERE id = :id");
    query.bindValue(":id", type_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select mark request"};
    if (!query.next())
        return {};
    QString name = query.value(query.record().indexOf("name")).toString();
    return QSharedPointer<QPair<int, MachineMark::MachineType>>::create(type_id, MachineMark::MachineType{std::move(name)});
}

QSharedPointer<QPair<int, MachineMark>> db::get_machine_mark(const QSqlDatabase& db, const int& mark_id) {
    QSqlQuery query{db};
    query.prepare("SELECT * FROM machine_marks WHERE id = :id");
    query.bindValue(":id", mark_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select mark request"};
    if (!query.next())
        return {};
    int brand_id = query.value(query.record().indexOf("brand")).toInt();
    int type_id = query.value(query.record().indexOf("type")).toInt();
    return QSharedPointer<QPair<int, MachineMark>>::create(mark_id, MachineMark{std::move(get_machine_type(db, type_id)->second), std::move(get_machine_brand(db, brand_id)->second)});
}

QSharedPointer<QPair<int, MachineMark>> db::get_machine_mark(const QSqlDatabase& db, const int& type_id, const int& brand_id) {
    QSqlQuery query{db};
    query.prepare("SELECT * FROM machine_marks WHERE brand = :brand AND type = :type");
    query.bindValue(":brand", brand_id);
    query.bindValue(":type", type_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select mark request"};
    if (!query.next())
        return {};
    int mark_id = query.value(query.record().indexOf("id")).toInt();
    return QSharedPointer<QPair<int, MachineMark>>::create(mark_id, MachineMark{std::move(get_machine_type(db, type_id)->second), std::move(get_machine_brand(db, brand_id)->second)});
}

QSharedPointer<QPair<int, Machine>> db::get_machine(const QSqlDatabase& db, const int& machine_id) {
    QSqlQuery query{db};
    query.prepare("SELECT * FROM machines WHERE id = :machine_id");
    query.bindValue(":machine_id", machine_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select machine request"};
    if (!query.next())
        return {};
    int owner_id = query.value(query.record().indexOf("owner")).toInt();
    QSharedPointer<QPair<int, User>> owner = db::get_user(db, owner_id);
    QString name = query.value(query.record().indexOf("name")).toString();
    QSharedPointer<QPair<int, MachineMark>> mark = db::get_machine_mark(db, query.value(query.record().indexOf("mark")).toInt());
    return QSharedPointer<QPair<int, Machine>>::create(QPair<int, Machine>{machine_id, Machine{std::move(name), QSharedPointer<User>::create(std::move(owner->second)), QSharedPointer<MachineMark>::create(std::move(mark->second))}});
}

QSharedPointer<QPair<int, Machine>> db::get_machine_by_order(const QSqlDatabase& db, const int& order_id) {
    QSqlQuery query{db};
    query.prepare("SELECT machine FROM orders WHERE id = :order_id");
    query.bindValue(":order_id", order_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select machine request"};
    if (!query.next())
        return {};
    return db::get_machine(db, query.value("machine").toInt());
}

QSharedPointer<QPair<int, Service>> db::get_service(const QSqlDatabase& db, const int& machine_id, const int& service_id) {
    QSqlQuery query{db};
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
    return QSharedPointer<QPair<int, Service>>::create(QPair<int, Service>{service_id, Service{std::move(name), std::move(duration), std::move(price)}});

}

QSharedPointer<QPair<int, Order>> db::get_order(const QSqlDatabase& db, const int& order_id) {
    QSqlQuery query{db};
    query.prepare("SELECT * FROM orders WHERE id = :order_id");
    query.bindValue(":order_id", order_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select order request"};
    if (!query.next())
        return {};
    QSharedPointer<User> customer = QSharedPointer<User>::create(get_user(db, query.value("customer").toInt())->second);
    QSharedPointer<Service> service = QSharedPointer<Service>::create(get_service(db, query.value("machine").toInt(), query.value("service").toInt())->second);
    QSharedPointer<Machine> machine = QSharedPointer<Machine>::create(get_machine(db, query.value("machine").toInt())->second);
    QDate date_start = query.value("date_start").toDate();
    Order order{date_start, customer, machine, service};
    if (query.value("complete").toBool()) {
        order.set_complete(true);
        order.set_date_end(query.value("date_end").toDate());
        order.set_description(query.value("description").toString());
    }
    if (!query.isNull("executor"))
        order.set_executor(QSharedPointer<User>::create(get_user(db, query.value("executor").toInt())->second));
    return QSharedPointer<QPair<int, Order>>::create(QPair<int, Order>{order_id, std::move(order)});
}

QVector<QPair<int, Machine>> db::get_machines(const QSqlDatabase& db, const int& owner_id) {
    QSqlQuery query{db};
    query.prepare("SELECT * FROM machines WHERE owner = :owner_id");
    query.bindValue(":owner_id", owner_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select machines request"};
    QVector<QPair<int, Machine>> machines;
    QSharedPointer<QPair<int, User>> owner = db::get_user(db, owner_id);
    while (query.next()) {
        int machine_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        QSharedPointer<QPair<int, MachineMark>> mark = db::get_machine_mark(db, query.value(query.record().indexOf("mark")).toInt());
        machines.push_back({machine_id, Machine{std::move(name), QSharedPointer<User>::create(std::move(owner->second)), QSharedPointer<MachineMark>::create(std::move(mark->second))}});
    }
    return machines;
}

QVector<QPair<int, Service>> db::get_services(const QSqlDatabase& db, const int& machine_id) {
    QSqlQuery query{db};
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
    QVector<QPair<int, Service>> services;
    while (query.next()) {
        int service_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        unsigned int duration_months = query.value("duration_months").toUInt();
        unsigned int duration_days = query.value("duration_days").toUInt();
        unsigned int duration_hours = query.value("duration_hours").toUInt();
        unsigned int duration_minutes = query.value("duration_minutes").toUInt();
        Duration duration{duration_months, duration_days, duration_hours, duration_minutes};
        double price = query.value("price").toDouble();
        services.push_back({service_id, Service{std::move(name), std::move(duration), std::move(price)}});
    }
    return services;
}

QVector<QPair<int, MachineMark::MachineType>> db::get_machine_types(const QSqlDatabase& db) {
    QSqlQuery query{db};
    if (!query.exec("SELECT * FROM machine_types"))
        throw std::runtime_error{"Failed to select services request"};
    QVector<QPair<int, MachineMark::MachineType>> types;
    while (query.next()) {
        int type_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        types.push_back({type_id, MachineMark::MachineType{std::move(name)}});
    }
    return types;
}

QVector<QPair<int, MachineMark::MachineBrand>> db::get_machine_brands(const QSqlDatabase& db, const int& type_id) {
    QSqlQuery query{db};
    query.prepare(R"!!!(
    SELECT machine_brands.id AS id, machine_brands.name
        FROM machine_marks
        JOIN machine_brands ON machine_marks.brand = machine_brands.id
        WHERE machine_marks.type = :type_id
)!!!");
    query.bindValue(":type_id", type_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select brands request"};
    QVector<QPair<int, MachineMark::MachineBrand>> brands;
    while (query.next()) {
        int brand_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        brands.push_back({brand_id, MachineMark::MachineBrand{std::move(name)}});
    }
    return brands;
}

QVector<QPair<int, User>> db::get_users(const QSqlDatabase& db) {
    QSqlQuery query{db};
    query.prepare(R"!!!(
    SELECT * FROM users;
)!!!");
    if (!query.exec())
        throw std::runtime_error{"Failed to select users request"};
    QVector<QPair<int, User>> users;
    while (query.next()) {
        int user_id = query.value(query.record().indexOf("id")).toInt();
        QString name = query.value(query.record().indexOf("name")).toString();
        QString login = query.value("login").toString();
        QString password = query.value("password").toString();
        UserRole role = role_by_str(query.value("role").toString());
        users.push_back({user_id, User{std::move(name), std::move(login), std::move(password), std::move(role)}});
    }
    return users;
}

QVector<QPair<int, Order>> db::get_aviable_orders(const QSqlDatabase& db) {
    QSqlQuery query{db};
    if (!query.exec(R"!!!(
                    SELECT id, customer, machine, service, date_start
                    FROM orders
                    WHERE executor is NULL AND complete = false;
            )!!!"))
        throw std::runtime_error{"Failed to select aviable orders request"};
    QVector<QPair<int, Order>> orders;
    while (query.next()) {
        int order_id = query.value("id").toInt();
        QSharedPointer<User> customer = QSharedPointer<User>::create(get_user(db, query.value("customer").toInt())->second);
        QSharedPointer<Service> service = QSharedPointer<Service>::create(get_service(db, query.value("machine").toInt(), query.value("service").toInt())->second);
        QSharedPointer<Machine> machine = QSharedPointer<Machine>::create(get_machine(db, query.value("machine").toInt())->second);
        QDate date_start = query.value("date_start").toDate();
        orders.push_back({order_id, Order{date_start, customer, machine, service}});
    }
    return orders;
}

QVector<QPair<int, Order>> db::get_active_orders(const QSqlDatabase& db, const int& user_id) {
    QSqlQuery query{db};
    query.prepare(R"!!!(
                    SELECT id, customer, machine, service, date_start
                    FROM orders
                    WHERE executor = :user_id AND complete = false;
            )!!!");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select active orders"};
    QVector<QPair<int, Order>> orders;
    while (query.next()) {
        int order_id = query.value("id").toInt();
        QSharedPointer<User> customer = QSharedPointer<User>::create(get_user(db, query.value("customer").toInt())->second);
        QSharedPointer<Service> service = QSharedPointer<Service>::create(get_service(db, query.value("machine").toInt(), query.value("service").toInt())->second);
        QSharedPointer<Machine> machine = QSharedPointer<Machine>::create(get_machine(db, query.value("machine").toInt())->second);
        QDate date_start = query.value("date_start").toDate();
        orders.push_back({order_id, Order{date_start, customer, machine, service}});
    }
    return orders;
}

QVector<QPair<int, Order>> db::get_machine_orders(const QSqlDatabase& db, const int& machine_id) {
    QSqlQuery query{db};
    query.prepare(R"!!!(
                    SELECT *
                    FROM orders
                    WHERE machine = :machine_id;
            )!!!");
    query.bindValue(":machine_id", machine_id);
    if (!query.exec())
        throw std::runtime_error{"Failed to select active orders"};
    QVector<QPair<int, Order>> orders;
    while (query.next()) {
        int order_id = query.value("id").toInt();
        orders.push_back(*db::get_order(db, order_id));
    }
    return orders;
}
