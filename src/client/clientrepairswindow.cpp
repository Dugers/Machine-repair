#include "clientrepairswindow.h"
#include "tools/messages.h"
#include "ui_clientrepairswindow.h"
#include "clientareawindow.h"
#include "../models/db.h"
#include <QMessageBox>
#include "authwindow.h"

ClientRepairsWindow::ClientRepairsWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientRepairsWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
    auto machines = db::get_machines(mUser_id);
    for (auto const& machine: machines)
        this->ui->machine_combo_box->addItem(machine.name(), machine.id());
}
ClientRepairsWindow::~ClientRepairsWindow()
{
    delete ui;
}

void ClientRepairsWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new ClientAreaWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}


void ClientRepairsWindow::on_order_button_clicked()
{
    ERROR_CHECK_BEGIN
    int machine_id = this->ui->machine_combo_box->currentData().toInt();
    int repair_id = this->ui->repair_combo_box->currentData().toInt();
    if (!db::create_order(mUser_id, machine_id, repair_id))
        throw std::runtime_error{"Не удалось выполнить операцию, возможные причины:\n1) Проблемы с базой данных \n2) Для данного станка уже выполняется выбранная услуга"};
    show_info("Заявка успешно принята в обработку", false, this);
    ERROR_CHECK_END(this)
}


void ClientRepairsWindow::on_repair_combo_box_currentIndexChanged(int index)
{
    if (index == -1) {
        this->ui->order_button->setEnabled(false);
        this->ui->execution_time_line_edit->setText("");
        this->ui->execution_cost_line_edit->setText("");
        return;
    }
    ERROR_CHECK_BEGIN
    int machine_id = this->ui->machine_combo_box->currentData().toInt();
    int repair_id = this->ui->repair_combo_box->currentData().toInt();
    QSharedPointer<ServiceSql> service = db::get_service(machine_id, repair_id);
    if (!service)
        throw std::runtime_error{"Произошла ошибка в получении данных об услуге"};
    this->ui->execution_time_line_edit->setText(service->durtaion());
    this->ui->execution_cost_line_edit->setText(QString::number(service->price()));
    this->ui->order_button->setEnabled(true);
    ERROR_CHECK_END(this)
}


void ClientRepairsWindow::on_machine_combo_box_currentIndexChanged(int index)
{
    ERROR_CHECK_BEGIN
    int machine_id = this->ui->machine_combo_box->currentData().toInt();
    QVector<ServiceSql> repairs = db::get_services(machine_id);
    this->ui->repair_combo_box->clear();
    for (auto const& repair: repairs)
        this->ui->repair_combo_box->addItem(repair.name(), repair.id());
    this->ui->repair_combo_box->setEnabled(true);
    ERROR_CHECK_END(this)
}

