#include "listrepairsmachinewindow.h"
#include "tools/messages.h"
#include "ui_listrepairsmachinewindow.h"
#include "../models/db.h"
#include "workerareawindow.h"
#include "aboutorderwindow.h"
#include <QMessageBox>
#include "authwindow.h"
#include "tools/widgets.h"

ListRepairsMachineWindow::ListRepairsMachineWindow(const int& user_id, const int& mMachine_id, QWidget *parent) :
    QWidget(parent),
    PermissionController<UserRole::Worker>{user_id},
    ui(new Ui::ListRepairsMachineWindow),
    mOrders{db::get_machine_orders(mMachine_id)}
{
    ui->setupUi(this);
    QVector<QVector<QString>> str_orders;
    for (auto const& order : mOrders) {
        str_orders.push_back(order.str_values(false, false));
    }
    fill_table(ui->orders_table_widget, str_orders);
}

ListRepairsMachineWindow::~ListRepairsMachineWindow()
{
    delete ui;
}

void ListRepairsMachineWindow::on_about_button_clicked()
{
    ERROR_CHECK_BEGIN
    if (ui->orders_table_widget->currentRow() == -1)
        throw std::runtime_error{"Выберите заказ"};
    open_window(new AboutOrderWindow{user_id(), mOrders[ui->orders_table_widget->currentRow()].id()}, this);
    ERROR_CHECK_END(this)
}


void ListRepairsMachineWindow::on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item)
{
    ERROR_CHECK_BEGIN
    on_about_button_clicked();
    ERROR_CHECK_END(this)
}


void ListRepairsMachineWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new WorkerAreaWindow{user_id()}, this);
    ERROR_CHECK_END(this)
}

