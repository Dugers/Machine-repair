#include "aviableorderslistwindow.h"
#include "ui_aviableorderslistwindow.h"
#include "../models/db.h"
#include "workerareawindow.h"
#include "aboutorderwindow.h"
#include <QMessageBox>

AviableOrdersListWindow::AviableOrdersListWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AviableOrdersListWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
    for (int i = 0; i < ui->orders_table_widget->columnCount(); ++i)
        ui->orders_table_widget->setColumnWidth(i, ui->orders_table_widget->width()/ui->orders_table_widget->columnCount());
    mAviable_orders = db::get_aviable_orders();
    for (auto const& aviable_order: mAviable_orders) {
        if (!aviable_order.machine() || !aviable_order.machine()->mark() || !aviable_order.service())
            throw std::invalid_argument{"Не получилось отобразить данные заказа"};
        ui->orders_table_widget->setRowCount(ui->orders_table_widget->rowCount()+1);
        int row_index = ui->orders_table_widget->rowCount() - 1;
        ui->orders_table_widget->setItem(row_index, 0, new QTableWidgetItem{aviable_order.machine()->mark()->type().name()});
        ui->orders_table_widget->setItem(row_index, 1, new QTableWidgetItem{aviable_order.machine()->mark()->brand().name()});
        ui->orders_table_widget->setItem(row_index, 2, new QTableWidgetItem{aviable_order.service()->name()});
    }
}

AviableOrdersListWindow::~AviableOrdersListWindow()
{
    delete ui;
}

void AviableOrdersListWindow::on_take_order_button_clicked()
{
    QMessageBox msgBox{this};
    try {
        if (ui->orders_table_widget->currentRow() == -1)
            throw std::runtime_error{"Выберите заказ"};
        if (db::get_worker_orders_count(mUser_id) >= 1)
            throw std::runtime_error{"Нельзя выполнять одновременно больше одного заказа"};
        if (!db::update_order_executor(mAviable_orders[ui->orders_table_widget->currentRow()].id(), mUser_id))
            throw std::runtime_error{"Не удалось взять заказ"};
        msgBox.setText("Заказ успешно взят");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        (new AviableOrdersListWindow{mUser_id})->show();
        this->close();
    }
    catch (std::exception e) {
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
}


void AviableOrdersListWindow::on_about_button_clicked()
{
    try {
        if (ui->orders_table_widget->currentRow() == -1)
            throw std::runtime_error{"Выберите заказ"};
        (new AboutOrderWindow{mUser_id, mAviable_orders[ui->orders_table_widget->currentRow()].id()})->show();
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


void AviableOrdersListWindow::on_go_area_button_clicked()
{
    (new WorkerAreaWindow{mUser_id})->show();
    this->close();
}


void AviableOrdersListWindow::on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item)
{
    on_about_button_clicked();
}

