#include "adminareawindow.h"
#include "ui_adminareawindow.h"
#include "listuserswindow.h"
#include "adduserwindow.h"
#include "../authwindow.h"
#include <QCloseEvent>

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
    (new AddUserWindow{mUser_id})->show();
    this->close();
}


void AdminAreaWindow::on_edit_user_button_clicked()
{
    (new ListUsersWindow{mUser_id})->show();
    this->close();

}


void AdminAreaWindow::on_exit_button_clicked()
{
    (new AuthWindow)->show();
    this->close();
}
