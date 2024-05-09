#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QVector>
//#include "../entities/basesqlobject.h"
#include "../entities/user.h"
#include "../entities/machine.h"
#include "../entities/service.h"
#include "../entities/order.h"
#include <QPair>

struct db {
private:
    static void create_enum_roles(const QSqlDatabase& db);
    static void create_table_users(const QSqlDatabase& db);
    static void create_table_machine_types(const QSqlDatabase& db);
    static void create_table_machine_brands(const QSqlDatabase& db);
    static void create_table_machine_marks(const QSqlDatabase& db);
    static void create_table_machines(const QSqlDatabase& db);
    static void create_table_services(const QSqlDatabase& db);
    static void create_table_services_marks(const QSqlDatabase& db);
    static void create_table_orders(const QSqlDatabase& db);
public:
    class PostgresPool{
    public:
        PostgresPool() = delete;
        static const QSqlDatabase& get();
    };
    // =================== CREATE =======================
    static void create_tables(const QSqlDatabase& db);
    static bool create_order(const QSqlDatabase& db, const int& customer_id, const int& machine_id, const int& service_id, const QDate& date_start = QDate::currentDate());
    static bool create_machine(const QSqlDatabase& db, const Machine& machine, const int& owner_id, const int& mark_id);
    static bool create_user(const QSqlDatabase& db, const User& user);
    static bool create_machine_mark(const QSqlDatabase& db, const int& type_id, const int& brand_id);
    // ==================== READ ========================
    static QSharedPointer<QPair<int, MachineMark>> get_machine_mark(const QSqlDatabase& db, const int& mark_id);
    static QSharedPointer<QPair<int, MachineMark>> get_machine_mark(const QSqlDatabase& db, const int& type_id, const int& brand_id);
    static QSharedPointer<QPair<int, MachineMark::MachineBrand>> get_machine_brand(const QSqlDatabase& db, const int& brand_id);
    static QSharedPointer<QPair<int, MachineMark::MachineType>> get_machine_type(const QSqlDatabase& db, const int& type_id);
    static QSharedPointer<QPair<int, User>> get_user(const QSqlDatabase& db, const int& user_id);
    static QSharedPointer<QPair<int, User>> get_user(const QSqlDatabase& db, const QString& user_login);
    static QSharedPointer<QPair<int, Machine>> get_machine(const QSqlDatabase& db, const int& machine_id);
    static QSharedPointer<QPair<int, Machine>> get_machine_by_order(const QSqlDatabase& db, const int& order_id);
    static QSharedPointer<QPair<int, Service>> get_service(const QSqlDatabase& db, const int& machine_id, const int& service_id);
    static QSharedPointer<QPair<int, Order>> get_order(const QSqlDatabase& db, const int& order_id);
    static QVector<QPair<int, Machine>> get_machines(const QSqlDatabase& db, const int& user_id);
    static QVector<QPair<int, Service>> get_services(const QSqlDatabase& db, const int& machine_id);
    static QVector<QPair<int, MachineMark::MachineType>> get_machine_types(const QSqlDatabase& db);
    static QVector<QPair<int, MachineMark::MachineBrand>> get_machine_brands(const QSqlDatabase& db, const int& type_id);
    static QVector<QPair<int, User>> get_users(const QSqlDatabase& db);
    static QVector<QPair<int, Order>> get_aviable_orders(const QSqlDatabase& db);
    static QVector<QPair<int, Order>> get_active_orders(const QSqlDatabase& db, const int& user_id);
    static QVector<QPair<int, Order>> get_machine_orders(const QSqlDatabase& db, const int& machine_id);
    static int get_client_orders_count(const QSqlDatabase& db, const int& user_id);
    static int get_worker_orders_count(const QSqlDatabase& db, const int& worker_id);
    static QSharedPointer<QDate> get_last_repair_date(const QSqlDatabase& db, const int& machine_id);
    // =================== UPDATE =======================
    static bool update_user_password(const QSqlDatabase& db, const int& user_id, const QString& new_password);
    static bool update_user_name(const QSqlDatabase& db, const int& user_id, const QString& new_name);
    static bool update_user_login(const QSqlDatabase& db, const int& user_id, const QString& new_login);
    static bool update_user_role(const QSqlDatabase& db, const int& user_id, const UserRole& new_role);
    static bool update_order_executor(const QSqlDatabase& db, const int& order_id, const int& executor_id);
    static bool complete_order(const QSqlDatabase& db, const int& order_id, const QString& description);
    // =================== DELETE =======================
    static bool delete_user(const QSqlDatabase& db, const int& user_id);
    static bool clear_tables(const QSqlDatabase& db);
    static bool drop_tables(const QSqlDatabase& db);
};

#endif // DB_H

