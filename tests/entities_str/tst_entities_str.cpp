#include "tst_entities_str.h"
#include "entities/user.h"
#include "entities/order.h"
#include "entities/machine.h"

entities_str::entities_str()
{

}

entities_str::~entities_str()
{

}

void entities_str::user_role()
{
    QVERIFY(str_by_role(UserRole::Client) == "Client");
    QVERIFY(str_by_role(UserRole::Worker) == "Worker");
    QVERIFY(str_by_role(UserRole::Admin) == "Admin");
    QVERIFY(str_by_role(UserRole::None) == "None");
    // ===========================================
    QVERIFY(role_by_str("ClieNT") == UserRole::Client);
    QVERIFY(role_by_str("WoRkER") == UserRole::Worker);
    QVERIFY(role_by_str("AdMiN") == UserRole::Admin);
    QVERIFY(role_by_str("ekjfewj$(09w4fowie1_@)f4") == UserRole::None);
}

void entities_str::user_str()
{
    const QString name = "Евгений";
    const QString login = "evgeniy";
    const QString password = "12345665";
    const UserRole role = UserRole::Client;
    const QString role_str = str_by_role(role);
    User user{name, login, password, role};
    QVector<QString> values = {name, login, password, role_str};
    QVERIFY(user.str_values(true, true, true, true) == values);
    values.pop_front();
    QVERIFY(user.str_values(false, true, true, true) == values);
    values.pop_front();
    QVERIFY(user.str_values(false, false, true, true) == values);
    values.pop_front();
    QVERIFY(user.str_values(false, false, false, true) == values);
    values.pop_front();
    QVERIFY(user.str_values(false, false, false, false) == values);
    values = {name, login, role_str};
    QVERIFY(user.str_values() == values);
}

void entities_str::order_str()
{
//    if (((machine_type || machine_brand) && (!mMachine || !mMachine->mark())) ||
//        (service_name && !mService) ||
//        (date_start && !mDate_start.isValid()))
//            throw std::invalid_argument{"Не получилось отобразить данные заказа"};
    Order order{{}, nullptr, nullptr, nullptr};
    QVector<QString> values;
    // ===============================================
    QVERIFY(order.str_status() == "Поиск исполнителя");
    QVERIFY(order.str_date_end() == "Еще не завершен");
    // ===============================================
    QVERIFY_EXCEPTION_THROWN(order.str_values(), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false, false), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false, false, false), std::invalid_argument);
    values = {order.str_date_end(), order.str_status()};
    QVERIFY(order.str_values(false, false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false, false) == values);
    // ===============================================
    order.set_date_end({2000, 3, 10});
    // ===============================================
    QVERIFY(order.str_status() == "Поиск исполнителя");
    QVERIFY(order.str_date_end() == "Еще не завершен");
    // ===============================================
    QVERIFY_EXCEPTION_THROWN(order.str_values(), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false, false), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false, false, false), std::invalid_argument);
    values = {order.str_date_end(), order.str_status()};
    QVERIFY(order.str_values(false, false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false, false) == values);
    // ===============================================
    order.set_date_start({2000, 2, 9});
    // ===============================================
    QVERIFY(order.str_status() == "Поиск исполнителя");
    QVERIFY(order.str_date_end() == "Еще не завершен");
    // ===============================================
    QVERIFY_EXCEPTION_THROWN(order.str_values(), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false, false), std::invalid_argument);
    values = {"09.02.2000", order.str_date_end(), order.str_status()};
    QVERIFY(order.str_values(false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false, false) == values);
    // ===============================================
    order.set_service(QSharedPointer<Service>::create("Диагностика", Duration{}, 1000));
    // ===============================================
    QVERIFY(order.str_status() == "Поиск исполнителя");
    QVERIFY(order.str_date_end() == "Еще не завершен");
    // ===============================================
    QVERIFY_EXCEPTION_THROWN(order.str_values(), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false), std::invalid_argument);
    values = {"Диагностика", "09.02.2000", order.str_date_end(), order.str_status()};
    QVERIFY(order.str_values(false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false, false) == values);
    // ===============================================
    order.set_machine(QSharedPointer<Machine>::create("123", nullptr, nullptr));
    // ===============================================
    QVERIFY(order.str_status() == "Поиск исполнителя");
    QVERIFY(order.str_date_end() == "Еще не завершен");
    // ===============================================
    QVERIFY_EXCEPTION_THROWN(order.str_values(), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(order.str_values(false), std::invalid_argument);
    values = {"Диагностика", "09.02.2000", order.str_date_end(), order.str_status()};
    QVERIFY(order.str_values(false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false, false) == values);
    // ===============================================
    order.set_machine(QSharedPointer<Machine>::create("123", nullptr,
                                                      QSharedPointer<MachineMark>::create(
                                                          MachineMark::MachineType("Type"),
                                                          MachineMark::MachineBrand("Brand")
                                                      )));
    // ===============================================
    QVERIFY(order.str_status() == "Поиск исполнителя");
    QVERIFY(order.str_date_end() == "Еще не завершен");
    // ===============================================
    values = {"Type", "Brand", "Диагностика", "09.02.2000", order.str_date_end(), order.str_status()};
    QVERIFY(order.str_values() == values);
    values.pop_front();
    QVERIFY(order.str_values(false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false) == values);
    values.pop_front();
    QVERIFY(order.str_values(false, false, false, false, false) == values);
    // ===============================================
    order.set_executor(QSharedPointer<User>::create("Евгений", "evgen", "1234566", UserRole::Worker));
    values = {order.str_status()};
    // ===============================================
    QVERIFY(order.str_status() == "Выполняется");
    QVERIFY(order.str_values(false, false, false, false, false) == values);
    // ===============================================
    order.set_complete(true);
    values = {order.str_status()};
    // ===============================================
    QVERIFY(order.str_status() == "Выполнен");
    QVERIFY(order.str_values(false, false, false, false, false) == values);
    QVERIFY(order.str_date_end() == "10.03.2000");
    // ===============================================
    order.set_date_end({});
    QVERIFY_EXCEPTION_THROWN(order.str_date_end(), std::invalid_argument);
}

void entities_str::machine_str()
{
    Machine machine{"machine", nullptr, nullptr};
    QVector<QString> values = {"machine"};
    QVERIFY(machine.str_values(true, false, false) == values);
    QVERIFY_EXCEPTION_THROWN(machine.str_values(false, false, true), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(machine.str_values(false, true, false), std::invalid_argument);
    QVERIFY_EXCEPTION_THROWN(machine.str_values(true), std::invalid_argument);
    machine.set_mark(QSharedPointer<MachineMark>::create(
                        MachineMark::MachineType("Type"),
                        MachineMark::MachineBrand("Brand")));
    values = {"machine", "Type", "Brand"};
    QVERIFY(machine.str_values() == values);
    values = {"machine", "Brand"};
    QVERIFY(machine.str_values(true, false, true) == values);
    values = {"machine", "Type"};
    QVERIFY(machine.str_values(true, true, false) == values);
    values = {"Type", "Brand"};
    QVERIFY(machine.str_values(false, true, true) == values);
}

QTEST_APPLESS_MAIN(entities_str)
