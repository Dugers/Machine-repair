#include "clientmachineswindow.h"
#include "ui_clientmachineswindow.h"
#include "clientareawindow.h"
#include "addmachinewindow.h"
#include "../models/db.h"
#include <QMessageBox>

ClientMachinesWindow::ClientMachinesWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientMachinesWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
    try{
        QVector<MachineSql> machines = db::get_machines(mUser_id);
            for (const MachineSql& machine : machines)
        this->ui->machines_list->addItem(machine.name());
    } catch (std::exception e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}

ClientMachinesWindow::~ClientMachinesWindow()
{
    delete ui;
}


void ClientMachinesWindow::on_add_button_clicked()
{
    (new AddMachineWindow{mUser_id})->show();
    this->close();
}


void ClientMachinesWindow::on_go_area_button_clicked()
{
    (new ClientAreaWindow{mUser_id})->show();
    this->close();
}

