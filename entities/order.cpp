#include "order.h"

Order::Order(const bool& complete, const QDate& date_start, const QDate& date_end, const QString& description, const QSharedPointer<const User>& customer,
    const QSharedPointer<const User>& executor, const QSharedPointer<const Machine>& machine, const QSharedPointer<const Service>& service) :
    mComplete{complete},
    mDate_start{date_start},
    mDate_end{date_end},
    mDescription{description},
    mCustomer{customer},
    mExecutor{executor},
    mMachine{machine},
    mService{service} {};

Order::Order(const QDate& date_start, const QSharedPointer<const User>& customer,
    const QSharedPointer<const Machine>& machine, const QSharedPointer<const Service>& service):
mComplete{false},
    mDate_start{date_start},
    mDate_end{},
    mDescription{},
    mCustomer{customer},
    mExecutor{},
    mMachine{machine},
    mService{service} {};
void Order::set_date_start(const QDate& date) {
    mDate_start = date;
}
void Order::set_date_start(QDate&& date) noexcept {
    mDate_start = std::move(date);
}
void Order::set_date_end(const QDate& date) {
    mDate_end = date;
}
void Order::set_date_end(QDate&& date) noexcept {
    mDate_end = std::move(date);
}
void Order::set_description(const QString& description) {
    mDescription = description;
}
void Order::set_description(QString&& description) noexcept {
    mDescription = std::move(description);
}
void Order::set_customer(const QSharedPointer<const User>& customer) {
    mCustomer = customer;
}
void Order::set_customer(QSharedPointer<const User>&& customer) {
    mCustomer = std::move(customer);
}
void Order::set_executor(const QSharedPointer<const User>& executor) {
    mExecutor = executor;
}
void Order::set_executor(QSharedPointer<const User>&& executor) {
    mExecutor = std::move(executor);
}
void Order::set_machine(const QSharedPointer<const Machine>& machine) {
    mMachine = machine;
}
void Order::set_machine(QSharedPointer<const Machine>&& machine) {
    mMachine = std::move(machine);
}
void Order::set_service(const QSharedPointer<const Service>& service) {
    mService = service;
}
void Order::set_service(QSharedPointer<const Service>&& service) {
    mService = std::move(service);
}
void Order::set_complete(bool complete) {
    mComplete = complete;
}
const QDate& Order::date_start() const {
    return mDate_start;
}
const QDate& Order::date_end() const {
    return mDate_end;
}
const QString& Order::description() const {
    return mDescription;
}
const QSharedPointer<const User>& Order::customer() const {
    return mCustomer;
}
const QSharedPointer<const User>& Order::executor() const {
    return mExecutor;
}
const QSharedPointer<const Machine>& Order::machine() const {
    return mMachine;
}
const QSharedPointer<const Service>& Order::service() const {
    return mService;
}
const bool& Order::complete() const{
    return mComplete;
}
