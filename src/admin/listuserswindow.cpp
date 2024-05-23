#include "listuserswindow.h"
#include "tools/messages.h"
#include "ui_listuserswindow.h"
#include "adminareawindow.h"
#include "../models/db.h"
#include "../confirmationdialog.h"
#include <QMessageBox>
#include "adminareawindow.h"
#include "edituserwindow.h"
#include "../authwindow.h"
#include "tools/widgets.h"

ListUsersWindow::ListUsersWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListUsersWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
    QVector<QVector<QString>> users_str;
    for (auto const& user : db::get_users()) {
        QVector<QString> user_str = user.str_values();
        if (user.role() == UserRole::Client)
            user_str.push_back(QString::number(db::get_client_orders_count(user.id())));
        else if (user.role() == UserRole::Worker)
            user_str.push_back(QString::number(db::get_worker_orders_count(user.id())));
        else
            user_str.push_back("-");
        users_str.push_back(std::move(user_str));
    }
    fill_table(ui->users_table_widget, users_str);
}

ListUsersWindow::~ListUsersWindow()
{
    delete ui;
}

int ListUsersWindow::get_selected_user_id() const {
    const int current_row = this->ui->users_table_widget->currentRow();
    if (current_row == -1)
        throw std::runtime_error{"Пользователь не выбран"};
    const QSharedPointer<UserSql> selected_user = db::get_user(this->ui->users_table_widget->item(current_row, USER_LOGIN_COLUMN)->text());
    if (!selected_user)
        throw std::runtime_error{"Не удалось получить данные о пользователе"};
    return selected_user->id();
}

void ListUsersWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AdminAreaWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}


void ListUsersWindow::on_delete_button_clicked()
{
    ERROR_CHECK_BEGIN
    const int user_id = get_selected_user_id();
    if (!show_confirm(this)) return;
    if (!db::delete_user(user_id))
        throw std::runtime_error{"Не удалось удалить пользователя"};
    if (mUser_id != user_id)
        open_window(new AdminAreaWindow{mUser_id}, this);
    else
        open_window(new AuthWindow, this);
    ERROR_CHECK_END(this)
}


void ListUsersWindow::on_edit_button_clicked()
{
    ERROR_CHECK_BEGIN
    const int user_id = get_selected_user_id();
    open_window(new EditUserWindow{mUser_id, user_id}, this);
    ERROR_CHECK_END(this)
}


void ListUsersWindow::on_users_table_widget_itemDoubleClicked(QTableWidgetItem *item)
{
    return this->on_edit_button_clicked();
}

