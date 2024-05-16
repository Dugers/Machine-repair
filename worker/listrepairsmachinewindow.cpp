#include "listrepairsmachinewindow.h"
#include "ui_listrepairsmachinewindow.h"
#include "../models/db.h"
#include "workerareawindow.h"
#include "aboutorderwindow.h"
#include <QMessageBox>

ListRepairsMachineWindow::ListRepairsMachineWindow(const int& user_id, const int& mMachine_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListRepairsMachineWindow),
    mUser_id{user_id},
    mOrders{db::get_machine_orders(mMachine_id)}
{
    ui->setupUi(this);
    for (int i = 0; i < ui->orders_table_widget->columnCount(); ++i)
        ui->orders_table_widget->setColumnWidth(i, ui->orders_table_widget->width()/ui->orders_table_widget->columnCount());
    ui->orders_table_widget->setRowCount(mOrders.size());
    for (int i = 0; i < mOrders.size(); ++i) {
        if (!mOrders[i].service())
            throw std::invalid_argument{"Не получилось отобразить данные заказа"};
        ui->orders_table_widget->setItem(i, 0, new QTableWidgetItem{mOrders[i].service()->name()});
        ui->orders_table_widget->setItem(i, 1, new QTableWidgetItem{mOrders[i].date_start().toString("dd.MM.yyyy")});
        if (mOrders[i].complete()) {
            if (mOrders[i].date_end().isNull())
                throw std::invalid_argument{"Не получилось отобразить данные заказа"};
            ui->orders_table_widget->setItem(i, 2, new QTableWidgetItem{mOrders[i].date_end().toString("dd.MM.yyyy")});
            ui->orders_table_widget->setItem(i, 3, new QTableWidgetItem{"Выполнен"});
        }
        else {
            ui->orders_table_widget->setItem(i, 2, new QTableWidgetItem{"Еще не завершен"});
            if (mOrders[i].executor())
                ui->orders_table_widget->setItem(i, 3, new QTableWidgetItem{"Выполняется"});
            else
                ui->orders_table_widget->setItem(i, 3, new QTableWidgetItem{"Поиск исполнителя"});
        }
    }
}

ListRepairsMachineWindow::~ListRepairsMachineWindow()
{
    delete ui;
}

void ListRepairsMachineWindow::on_about_button_clicked()
{
    try {
        if (ui->orders_table_widget->currentRow() == -1)
            throw std::runtime_error{"Выберите заказ"};
        (new AboutOrderWindow{mUser_id, mOrders[ui->orders_table_widget->currentRow()].id()})->show();
        this->close();
    }
    catch (std::exception e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
}


void ListRepairsMachineWindow::on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item)
{
    on_about_button_clicked();
}


void ListRepairsMachineWindow::on_go_area_button_clicked()
{
    (new WorkerAreaWindow{mUser_id})->show();
    this->close();
}

