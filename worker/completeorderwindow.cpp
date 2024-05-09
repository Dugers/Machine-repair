#include "completeorderwindow.h"
#include "ui_completeorderwindow.h"
#include "workerareawindow.h"
#include <QMessageBox>
#include "../models/db.h"
#include "../confirmationdialog.h"

CompleteOrderWindow::CompleteOrderWindow(const int& user_id, const int& order_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompleteOrderWindow),
    mUser_id{user_id},
    mOrder_id{order_id}
{
    ui->setupUi(this);
}

CompleteOrderWindow::~CompleteOrderWindow()
{
    delete ui;
}

void CompleteOrderWindow::on_complete_order_button_clicked()
{
    QMessageBox msgBox{this};
    try {
        QString description = ui->description_order_text_edit->toPlainText().simplified();
        validate_description(description);
        ConfirmationDialog confirm_dialog{this};
        confirm_dialog.setModal(true);
        if (!confirm_dialog.exec())
            return;
        if (!db::complete_order(db::PostgresPool::get(), mOrder_id, description))
            throw std::runtime_error{"Не удалось завершить заказ"};
        msgBox.setText("Заказ успешно завершен");
        msgBox.setIcon(QMessageBox::Information);
        on_go_area_button_clicked();
    }
    catch (std::exception e) {
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
}


void CompleteOrderWindow::on_go_area_button_clicked()
{
    (new WorkerAreaWindow{mUser_id})->show();
    this->close();
}

void CompleteOrderWindow::validate_description(const QString& description) {
    if (description != description.simplified())
        throw std::runtime_error{"Описание содержит лишние пробелы"};
    if (description.size() <= 10)
        throw std::runtime_error{"Описание слишком короткое"};
}

