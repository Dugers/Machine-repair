#include "clientareawindow.h"
#include "ui_clientareawindow.h"
#include "clientmachineswindow.h"
#include "clientrepairswindow.h"
#include "../authwindow.h"

ClientAreaWindow::ClientAreaWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientAreaWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
}

ClientAreaWindow::~ClientAreaWindow()
{
    delete ui;
}

void ClientAreaWindow::on_list_services_button_clicked()
{
    (new ClientRepairsWindow(mUser_id))->show();
    this->close();
}


void ClientAreaWindow::on_my_machines_button_clicked()
{
    (new ClientMachinesWindow(mUser_id))->show();
    this->close();
}


void ClientAreaWindow::on_exit_button_clicked()
{
    (new AuthWindow)->show();
    this->close();
}

