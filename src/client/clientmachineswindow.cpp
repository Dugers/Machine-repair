#include "clientmachineswindow.h"
#include "tools/messages.h"
#include "ui_clientmachineswindow.h"
#include "clientareawindow.h"
#include "addmachinewindow.h"
#include "../models/db.h"
#include <QMessageBox>
#include "authwindow.h"

ClientMachinesWindow::ClientMachinesWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    PermissionController<UserRole::Client>{user_id},
    ui(new Ui::ClientMachinesWindow)
{
    ui->setupUi(this);
    QVector<MachineSql> machines = db::get_machines(this->user_id());
    for (const MachineSql& machine : machines)
        this->ui->machines_list->addItem(machine.name());
}

ClientMachinesWindow::~ClientMachinesWindow()
{
    delete ui;
}


void ClientMachinesWindow::on_add_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AddMachineWindow{user_id()}, this);
    ERROR_CHECK_END(this)
}


void ClientMachinesWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new ClientAreaWindow{user_id()}, this);
    ERROR_CHECK_END(this)
}

