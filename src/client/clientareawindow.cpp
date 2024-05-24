#include "clientareawindow.h"
#include "tools/messages.h"
#include "ui_clientareawindow.h"
#include "clientmachineswindow.h"
#include "clientrepairswindow.h"
#include "../authwindow.h"

ClientAreaWindow::ClientAreaWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    PermissionController<UserRole::Client>{user_id},
    ui(new Ui::ClientAreaWindow)
{
    ui->setupUi(this);
}

ClientAreaWindow::~ClientAreaWindow()
{
    delete ui;
}

void ClientAreaWindow::on_list_services_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new ClientRepairsWindow(user_id()), this);
    ERROR_CHECK_END(this)
}


void ClientAreaWindow::on_my_machines_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new ClientMachinesWindow(user_id()), this);
    ERROR_CHECK_END(this)
}


void ClientAreaWindow::on_exit_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AuthWindow, this);
    ERROR_CHECK_END(this)
}

