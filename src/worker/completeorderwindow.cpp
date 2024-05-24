#include "completeorderwindow.h"
#include "tools/messages.h"
#include "ui_completeorderwindow.h"
#include "workerareawindow.h"
#include <QMessageBox>
#include "../models/db.h"
#include "../confirmationdialog.h"
#include "authwindow.h"

CompleteOrderWindow::CompleteOrderWindow(const int& user_id, const int& order_id, QWidget *parent) :
    QWidget(parent),
    PermissionController<UserRole::Worker>{user_id},
    ui(new Ui::CompleteOrderWindow),
    mOrder_id{order_id}
{
    ui->setupUi(this);
}

CompleteOrderWindow::~CompleteOrderWindow()
{
    delete ui;
}

void CompleteOrderWindow::on_complete_order_button_clicked()
{
    ERROR_CHECK_BEGIN
    confirm();
    QString description = ui->description_order_text_edit->toPlainText().simplified();
    validate_description(description);
    if (!show_confirm(this))
        return;
    if (!db::complete_order(mOrder_id, description))
        throw std::runtime_error{"Не удалось завершить заказ"};
    show_info("Заказ успешно завершен", false, this);
    ERROR_CHECK_END(this)
}


void CompleteOrderWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new WorkerAreaWindow{user_id()}, this);
    ERROR_CHECK_END(this)
}

void CompleteOrderWindow::validate_description(const QString& description) {
    if (description != description.simplified())
        throw std::runtime_error{"Описание содержит лишние пробелы"};
    if (description.size() <= 10)
        throw std::runtime_error{"Описание слишком короткое"};
}

void CompleteOrderWindow::confirm() {
    PermissionController<UserRole::Worker>::confirm();
    QSharedPointer<OrderSql> order = db::get_order(mOrder_id);
    if (!order->executor())
        throw permission_error{"У вас недостаточно прав для этого действия!"};
    QSharedPointer<UserSql> executor = db::get_user(order->executor()->login());
    if (executor->id() != user_id())
        throw permission_error{"У вас недостаточно прав для этого действия!"};
}
