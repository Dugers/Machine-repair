#include "aboutmachinewindow.h"
#include "tools/messages.h"
#include "ui_aboutmachinewindow.h"
#include "../models/db.h"
#include "listrepairsmachinewindow.h"
#include "workerareawindow.h"
#include "authwindow.h"

AboutMachineWindow::AboutMachineWindow(const int& user_id, const int& machine_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutMachineWindow),
    mUser_id{user_id},
    mMachine_id{machine_id}
{
    ui->setupUi(this);
    auto machine = db::get_machine(mMachine_id);
    this->ui->type_line_edit->setText(machine->mark()->type().name());
    this->ui->brand_line_edit->setText(machine->mark()->brand().name());
    QString text{"Еще не было"};
    if (auto last_repair_date = db::get_last_repair_date(mMachine_id); last_repair_date)
        text = last_repair_date->toString("dd.MM.yyyy");
    this->ui->last_repair_line_edit->setText(text);
}

AboutMachineWindow::~AboutMachineWindow()
{
    delete ui;
}

void AboutMachineWindow::on_order_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new ListRepairsMachineWindow{mUser_id, mMachine_id}, this);
    ERROR_CHECK_END(this)
}


void AboutMachineWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new WorkerAreaWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}

