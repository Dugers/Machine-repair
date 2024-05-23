#ifndef ORDER_H
#define ORDER_H
#include <QString>
#include <QSharedPointer>
#include "machine.h"
#include "user.h"
#include "service.h"
#include <QDate>
#include "relationship_wrapper.h"

class Order
{
private:
    bool mComplete;
    QDate mDate_start;
    QDate mDate_end;
    QString mDescription;
    QSharedPointer<const User> mCustomer;
    QSharedPointer<const User> mExecutor;
    QSharedPointer<const Machine> mMachine;
    QSharedPointer<const Service> mService;
public:
    Order(const bool& complete, const QDate& date_start, const QDate& date_end, const QString& description, const QSharedPointer<const User>& customer,
    const QSharedPointer<const User>& executor, const QSharedPointer<const Machine>& machine, const QSharedPointer<const Service>& service);
    Order(const QDate& date_start, const QSharedPointer<const User>& customer,
    const QSharedPointer<const Machine>& machine, const QSharedPointer<const Service>& service);
    Order(const Order& order) = default;
    Order(Order&& order) noexcept = default;
    void set_date_start(const QDate& date);
    void set_date_start(QDate&& date) noexcept;
    void set_date_end(const QDate& date);
    void set_date_end(QDate&& date) noexcept;
    void set_description(const QString& description);
    void set_description(QString&& description) noexcept;
    void set_customer(const QSharedPointer<const User>& customer);
    void set_customer(QSharedPointer<const User>&& customer);
    void set_executor(const QSharedPointer<const User>& executor);
    void set_executor(QSharedPointer<const User>&& executor);
    void set_machine(const QSharedPointer<const Machine>& machine);
    void set_machine(QSharedPointer<const Machine>&& machine);
    void set_service(const QSharedPointer<const Service>& service);
    void set_service(QSharedPointer<const Service>&& service);
    void set_complete(bool complete);
    QVector<QString> str_values(bool machine_type = true, bool machine_brand = true, bool service_name = true, bool date_start = true, bool date_end = true, bool status = true) const;
    QString str_status() const;
    QString str_date_end() const;
    const QDate& date_start() const;
    const QDate& date_end() const;
    const QString& description() const;
    const QSharedPointer<const User>& customer() const;
    const QSharedPointer<const User>& executor() const;
    const QSharedPointer<const Machine>& machine() const;
    const QSharedPointer<const Service>& service() const;
    const bool& complete() const;
    Order& operator=(const Order& order) = default;
    Order& operator=(Order&& order) noexcept = default;
};

class OrderSql :
    public Order,
    public SqlObject
{
public:
    OrderSql(const bool& complete, const QDate& date_start, const QDate& date_end, const QString& description,
             const QSharedPointer<const User>& customer, const QSharedPointer<const User>& executor,
             const QSharedPointer<const Machine>& machine, const QSharedPointer<const Service>& service, const int& id);

    OrderSql(const QDate& date_start, const QSharedPointer<const User>& customer,
             const QSharedPointer<const Machine>& machine, const QSharedPointer<const Service>& service, const int& id);

    OrderSql(bool&& complete, QDate&& date_start, QDate&& date_end, QString&& description,
             QSharedPointer<const User>&& customer, QSharedPointer<const User>&& executor,
             QSharedPointer<const Machine>&& machine, QSharedPointer<const Service>&& service, int&& id) noexcept;

    OrderSql(Order&& order, const int& id);
};

#endif // ORDER_H
