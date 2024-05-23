#include "workerareawindow.h"
#include "tools/messages.h"
#include "ui_workerareawindow.h"
#include "aviableorderslistwindow.h"
#include "activeorderslistwindow.h"
#include "../authwindow.h"

WorkerAreaWindow::WorkerAreaWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerAreaWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
}

WorkerAreaWindow::~WorkerAreaWindow()
{
    delete ui;
}

void WorkerAreaWindow::on_aviable_orders_list_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AviableOrdersListWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}


void WorkerAreaWindow::on_active_orders_list_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new ActiveOrdersListWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}


void WorkerAreaWindow::on_exit_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AuthWindow, this);
    ERROR_CHECK_END(this)
}
