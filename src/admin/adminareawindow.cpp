#include "adminareawindow.h"
#include "tools/messages.h"
#include "ui_adminareawindow.h"
#include "listuserswindow.h"
#include "adduserwindow.h"
#include "../authwindow.h"

AdminAreaWindow::AdminAreaWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminAreaWindow),
    mUser_id{user_id}
{
    ui->setupUi(this);
}

AdminAreaWindow::~AdminAreaWindow()
{
    delete ui;
}

void AdminAreaWindow::on_add_user_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AddUserWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}


void AdminAreaWindow::on_edit_user_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new ListUsersWindow{mUser_id}, this);
    ERROR_CHECK_END(this)

}


void AdminAreaWindow::on_exit_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AuthWindow, this);
    ERROR_CHECK_END(this)
}
