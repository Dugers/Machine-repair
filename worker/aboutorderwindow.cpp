#include "aboutorderwindow.h"
#include "ui_aboutorderwindow.h"
#include "workerareawindow.h"
#include "aboutmachinewindow.h"
#include "../models/db.h"

AboutOrderWindow::AboutOrderWindow(const int& user_id, const int& order_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutOrderWindow),
    mUser_id{user_id},
    mOrder{std::move(*db::get_order(order_id))}
{
    ui->setupUi(this);
    if (!mOrder.complete()) {
        ui->description_order_label->close();
        ui->description_order_text_edit->close();
        ui->date_end_label->close();
        ui->date_end_line_edit->close();
        ui->about_machine_button->move(140, 260);
        ui->go_area_button->move(630, 260);
        this->setMinimumHeight(340);
        this->setMaximumHeight(340);
        if (!mOrder.executor())
            ui->status_order_line_edit->setText("Поиск исполнителя");
        else
            ui->status_order_line_edit->setText("Выполняется");
    }
    else {
        ui->description_order_text_edit->setText(mOrder.description());
        ui->date_end_line_edit->setText(mOrder.date_end().toString("dd.MM.yyyy"));
        ui->status_order_line_edit->setText("Выполнен");
    }
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

void AboutOrderWindow::on_about_machine_button_clicked()
{
    (new AboutMachineWindow{mUser_id, db::get_machine_by_order(mOrder.id())->id()})->show();
    this->close();
}


void AboutOrderWindow::on_go_area_button_clicked()
{
    (new WorkerAreaWindow{mUser_id})->show();
    this->close();
}

