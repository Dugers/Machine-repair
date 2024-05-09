#include "clientrepairswindow.h"
#include "ui_clientrepairswindow.h"
#include "clientareawindow.h"
#include "../models/db.h"
#include <QMessageBox>

ClientRepairsWindow::ClientRepairsWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientRepairsWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
    auto machines = db::get_machines(db::PostgresPool::get(), mUser_id);
    for (auto const& machine: machines)
        this->ui->machine_combo_box->addItem(machine.second.name(), machine.first);
}
ClientRepairsWindow::~ClientRepairsWindow()
{
    delete ui;
}

void ClientRepairsWindow::on_go_area_button_clicked()
{
    (new ClientAreaWindow{mUser_id})->show();
    this->close();
}


void ClientRepairsWindow::on_order_button_clicked()
{
    try {
        int machine_id = this->ui->machine_combo_box->currentData().toInt();
        int repair_id = this->ui->repair_combo_box->currentData().toInt();
        if (!db::create_order(db::PostgresPool::get(), mUser_id, machine_id, repair_id))
            throw std::runtime_error{"Не удалось выполнить операцию, возможные причины:\n1) Проблемы с базой данных \n2) Для данного станка уже выполняется выбранная услуга"};
        QMessageBox msgBox{this};
        msgBox.setText("Заявка успешно принята в обработку");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
    catch (std::exception e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}


void ClientRepairsWindow::on_repair_combo_box_currentIndexChanged(int index)
{
    if (index == -1) {
        this->ui->order_button->setEnabled(false);
        this->ui->execution_time_line_edit->setText("");
        this->ui->execution_cost_line_edit->setText("");
        return;
    }
    try {
        int machine_id = this->ui->machine_combo_box->currentData().toInt();
        int repair_id = this->ui->repair_combo_box->currentData().toInt();
        QSharedPointer<QPair<int, Service>> service = db::get_service(db::PostgresPool::get(), machine_id, repair_id);
        if (!service)
            throw std::runtime_error{"Произошла ошибка в получении данных об услуге"};
        this->ui->execution_time_line_edit->setText(service->second.durtaion());
        this->ui->execution_cost_line_edit->setText(QString::number(service->second.price()));
        this->ui->order_button->setEnabled(true);
    }
    catch (std::exception e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}


void ClientRepairsWindow::on_machine_combo_box_currentIndexChanged(int index)
{
    try {
        int machine_id = this->ui->machine_combo_box->currentData().toInt();
        QVector<QPair<int, Service>> repairs = db::get_services(db::PostgresPool::get(), machine_id);
        this->ui->repair_combo_box->clear();
        for (auto const& repair: repairs)
            this->ui->repair_combo_box->addItem(repair.second.name(), repair.first);
        this->ui->repair_combo_box->setEnabled(true);
    }
    catch (std::exception e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}

