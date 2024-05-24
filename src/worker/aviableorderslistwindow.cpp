#include "aviableorderslistwindow.h"
#include "tools/messages.h"
#include "tools/widgets.h"
#include "ui_aviableorderslistwindow.h"
#include "../models/db.h"
#include "workerareawindow.h"
#include "aboutorderwindow.h"
#include <QMessageBox>
#include "authwindow.h"

AviableOrdersListWindow::AviableOrdersListWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    PermissionController<UserRole::Worker>{user_id},
    ui(new Ui::AviableOrdersListWindow),
    mAviable_orders{db::get_aviable_orders()}
{
    ui->setupUi(this);
    QVector<QVector<QString>> str_orders;
    for (auto const& aviable_order: mAviable_orders)
        str_orders.push_back(aviable_order.str_values(true, true, true, false, false, false));
    fill_table(ui->orders_table_widget, str_orders);
}

AviableOrdersListWindow::~AviableOrdersListWindow()
{
    delete ui;
}

void AviableOrdersListWindow::on_take_order_button_clicked()
{
    ERROR_CHECK_BEGIN
    confirm();
    if (ui->orders_table_widget->currentRow() == -1)
        throw std::runtime_error{"Выберите заказ"};
    if (db::get_worker_orders_count(user_id()) >= 1)
        throw std::runtime_error{"Нельзя выполнять одновременно больше одного заказа"};
    if (!db::update_order_executor(mAviable_orders[ui->orders_table_widget->currentRow()].id(), user_id()))
        throw std::runtime_error{"Не удалось взять заказ"};
    show_info("Заказ успешно взят", false, this);
    open_window(new AviableOrdersListWindow{user_id()}, this);
    ERROR_CHECK_END(this)
}


void AviableOrdersListWindow::on_about_button_clicked()
{
    ERROR_CHECK_BEGIN
    if (ui->orders_table_widget->currentRow() == -1)
        throw std::runtime_error{"Выберите заказ"};
    open_window(new AboutOrderWindow{user_id(), mAviable_orders[ui->orders_table_widget->currentRow()].id()}, this);
    this->close();
    ERROR_CHECK_END(this)
}


void AviableOrdersListWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new WorkerAreaWindow{user_id()}, this);
    ERROR_CHECK_END(this)
}


void AviableOrdersListWindow::on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item)
{
    ERROR_CHECK_BEGIN
    on_about_button_clicked();
    ERROR_CHECK_END(this)
}

