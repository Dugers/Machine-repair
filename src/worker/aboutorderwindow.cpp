#include "aboutorderwindow.h"
#include "tools/messages.h"
#include "ui_aboutorderwindow.h"
#include "workerareawindow.h"
#include "aboutmachinewindow.h"
#include "../models/db.h"
#include "authwindow.h"

AboutOrderWindow::AboutOrderWindow(const int& user_id, const int& order_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutOrderWindow),
    mUser_id{user_id},
    mOrder{std::move(*db::get_order(order_id))}
{
    ui->setupUi(this);
    if (!mOrder.complete())
        hide_description();
    else {
        ui->description_order_text_edit->setText(mOrder.description());
        ui->date_end_line_edit->setText(mOrder.str_date_end());
    }
    ui->status_order_line_edit->setText(mOrder.str_status());
    ui->date_start_order_line_edit->setText(mOrder.date_start().toString("dd.MM.yyyy"));
    ui->name_service_line_edit->setText(mOrder.service()->name());
    ui->price_service_line_edit->setText(QString::number(mOrder.service()->price()));
    ui->type_machine_line_edit->setText(mOrder.machine()->mark()->type().name());
    ui->brand_machine_line_edit->setText(mOrder.machine()->mark()->brand().name());
}

AboutOrderWindow::~AboutOrderWindow()
{
    delete ui;
}

void AboutOrderWindow::hide_description() {
    ui->description_order_label->close();
    ui->description_order_text_edit->close();
    ui->date_end_label->close();
    ui->date_end_line_edit->close();
    ui->about_machine_button->move(140, 260);
    ui->go_area_button->move(630, 260);
    this->setMinimumHeight(340);
    this->setMaximumHeight(340);
}

void AboutOrderWindow::on_about_machine_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AboutMachineWindow{mUser_id, db::get_machine_by_order(mOrder.id())->id()}, this);
    ERROR_CHECK_END(this)
}


void AboutOrderWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new WorkerAreaWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}

