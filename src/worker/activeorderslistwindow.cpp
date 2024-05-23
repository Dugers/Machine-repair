#include "activeorderslistwindow.h"
#include "tools/messages.h"
#include "tools/widgets.h"
#include "ui_activeorderslistwindow.h"
#include "../models/db.h"
#include "workerareawindow.h"
#include "aboutorderwindow.h"
#include <QMessageBox>
#include "completeorderwindow.h"
#include "authwindow.h"

ActiveOrdersListWindow::ActiveOrdersListWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveOrdersListWindow),
    mUser_id{user_id},
    mActive_orders{db::get_active_orders(mUser_id)}
{
    ui->setupUi(this);
    QVector<QVector<QString>> str_orders;
    for (auto const& active_order: mActive_orders)
        str_orders.push_back(active_order.str_values(true, true, true, false, false, false));
    fill_table(ui->orders_table_widget, str_orders);
}

ActiveOrdersListWindow::~ActiveOrdersListWindow()
{
    delete ui;
}

void ActiveOrdersListWindow::on_about_button_clicked()
{
    ERROR_CHECK_BEGIN
    if (ui->orders_table_widget->currentRow() == -1)
        throw std::runtime_error{"Выберите заказ"};
    open_window(new AboutOrderWindow{mUser_id, mActive_orders[ui->orders_table_widget->currentRow()].id()}, this);
    this->close();
    ERROR_CHECK_END(this)
}


void ActiveOrdersListWindow::on_complete_order_button_clicked()
{
    ERROR_CHECK_BEGIN
    if (ui->orders_table_widget->currentRow() == -1)
        throw std::runtime_error{"Выберите заказ"};
    open_window(new CompleteOrderWindow{mUser_id, mActive_orders[ui->orders_table_widget->currentRow()].id()}, this);
    ERROR_CHECK_END(this)
}


void ActiveOrdersListWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new WorkerAreaWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}


void ActiveOrdersListWindow::on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item)
{
    ERROR_CHECK_BEGIN
    on_about_button_clicked();
    ERROR_CHECK_END(this)
}

