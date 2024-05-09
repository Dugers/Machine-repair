#include "workerareawindow.h"
#include "ui_workerareawindow.h"
#include "aviableorderslistwindow.h"
#include "activeorderslistwindow.h"
#include "../authwindow_.h"

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
    (new AviableOrdersListWindow{mUser_id})->show();
    this->close();
}


void WorkerAreaWindow::on_active_orders_list_button_clicked()
{
    (new ActiveOrdersListWindow{mUser_id})->show();
    this->close();
}


void WorkerAreaWindow::on_exit_button_clicked()
{
    (new AuthWindow)->show();
    this->close();
}

