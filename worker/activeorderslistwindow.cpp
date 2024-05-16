#include "activeorderslistwindow.h"
#include "ui_activeorderslistwindow.h"
#include "../models/db.h"
#include "workerareawindow.h"
#include "aboutorderwindow.h"
#include <QMessageBox>
#include "completeorderwindow.h"

ActiveOrdersListWindow::ActiveOrdersListWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveOrdersListWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
    for (int i = 0; i < ui->orders_table_widget->columnCount(); ++i)
        ui->orders_table_widget->setColumnWidth(i, ui->orders_table_widget->width()/ui->orders_table_widget->columnCount());
    mActive_orders = db::get_active_orders(mUser_id);
    for (auto const& active_order: mActive_orders) {
        if (!active_order.machine() || !active_order.machine()->mark() || !active_order.service())
            throw std::invalid_argument{"Не получилось отобразить данные заказа"};
        ui->orders_table_widget->setRowCount(ui->orders_table_widget->rowCount()+1);
        int row_index = ui->orders_table_widget->rowCount() - 1;
        ui->orders_table_widget->setItem(row_index, 0, new QTableWidgetItem{active_order.machine()->mark()->type().name()});
        ui->orders_table_widget->setItem(row_index, 1, new QTableWidgetItem{active_order.machine()->mark()->brand().name()});
        ui->orders_table_widget->setItem(row_index, 2, new QTableWidgetItem{active_order.service()->name()});
    }
}

ActiveOrdersListWindow::~ActiveOrdersListWindow()
{
    delete ui;
}

void ActiveOrdersListWindow::on_about_button_clicked()
{
    try {
        if (ui->orders_table_widget->currentRow() == -1)
            throw std::runtime_error{"Выберите заказ"};
        (new AboutOrderWindow{mUser_id, mActive_orders[ui->orders_table_widget->currentRow()].id()})->show();
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


void ActiveOrdersListWindow::on_complete_order_button_clicked()
{
    QMessageBox msgBox{this};
    try {
        if (ui->orders_table_widget->currentRow() == -1)
            throw std::runtime_error{"Выберите заказ"};
        (new CompleteOrderWindow{mUser_id, mActive_orders[ui->orders_table_widget->currentRow()].id()})->show();
        this->close();
    }
    catch (std::exception e) {
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
}


void ActiveOrdersListWindow::on_go_area_button_clicked()
{
    (new WorkerAreaWindow{mUser_id})->show();
    this->close();
}


void ActiveOrdersListWindow::on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item)
{
    on_about_button_clicked();
}

