#include "listuserswindow.h"
#include "ui_listuserswindow.h"
#include "adminareawindow.h"
#include "../models/db.h"
#include "../confirmationdialog.h"
#include <QMessageBox>
#include "adminareawindow.h"
#include "edituserwindow.h"
#include "../authwindow.h"

ListUsersWindow::ListUsersWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListUsersWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
    for (int i = 0; i < ui->users_table_widget->columnCount(); ++i)
        ui->users_table_widget->setColumnWidth(i, ui->users_table_widget->width()/ui->users_table_widget->columnCount());
    QVector<UserSql> users = db::get_users();
    ui->users_table_widget->setRowCount(users.size());
    for (int i = 0; i < users.size(); ++i) {
        ui->users_table_widget->setItem(i, 0, new QTableWidgetItem{users[i].name()});
        if (users[i].role() == UserRole::Client)
            ui->users_table_widget->setItem(i, 1, new QTableWidgetItem{QString::number(db::get_client_orders_count(users[i].id()))});
        else if (users[i].role() == UserRole::Worker)
            ui->users_table_widget->setItem(i, 1, new QTableWidgetItem{QString::number(db::get_worker_orders_count(users[i].id()))});
        else
            ui->users_table_widget->setItem(i, 1, new QTableWidgetItem{"-"});
        ui->users_table_widget->setItem(i, 2, new QTableWidgetItem{users[i].login()});
        ui->users_table_widget->setItem(i, 3, new QTableWidgetItem{str_by_role(users[i].role())});
    }
}

ListUsersWindow::~ListUsersWindow()
{
    delete ui;
}

void ListUsersWindow::on_go_area_button_clicked()
{
    (new AdminAreaWindow{mUser_id})->show();
    this->close();
}


void ListUsersWindow::on_delete_button_clicked()
{
    try {
        int current_row = this->ui->users_table_widget->currentRow();
        if (current_row == -1)
            throw std::runtime_error{"Сначала выберите пользователя"};
        ConfirmationDialog confirm_dialog(this);
        confirm_dialog.setModal(true);
        if (confirm_dialog.exec() == QDialog::Rejected)
            return;
        QSharedPointer<UserSql> selected_user = db::get_user(this->ui->users_table_widget->item(current_row, 2)->text());
        if (!selected_user)
            throw std::runtime_error{"Не удалось получить данные о пользователе"};
        if (!db::delete_user(selected_user->id()))
            throw std::runtime_error{"Не удалось удалить пользователя"};
        if (mUser_id != selected_user->id())
            (new AdminAreaWindow{mUser_id})->show();
        else
            (new AuthWindow)->show();
        this->close();
    }
    catch (std::exception& e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
}


void ListUsersWindow::on_edit_button_clicked()
{
    try {
        int current_row = this->ui->users_table_widget->currentRow();
        if (current_row == -1)
            throw std::runtime_error{"Сначала выберите пользователя"};
        QSharedPointer<UserSql> selected_user = db::get_user(this->ui->users_table_widget->item(current_row, 2)->text());
        if (!selected_user)
            throw std::runtime_error{"Не удалось получить данные о пользователе"};
        (new EditUserWindow{mUser_id, this->ui->users_table_widget->item(current_row, 2)->text()})->show();
        this->close();
    }
    catch (std::exception& e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
}


void ListUsersWindow::on_users_table_widget_itemDoubleClicked(QTableWidgetItem *item)
{
    return this->on_edit_button_clicked();
}

