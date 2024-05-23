#include <QMessageBox>
#include <QProcess>
#include <QFileDialog>
#include "authwindow.h"
#include "tools/messages.h"
#include "ui_authwindow.h"
#include "models/db.h"
#include "client/clientareawindow.h"
#include "admin/adminareawindow.h"
#include "worker/workerareawindow.h"
#include "config.h"

AuthWindow::AuthWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::on_auth_button_clicked()
{
    QString login = this->ui->login_line_edit->text();
    QString password = this->ui->password_line_edit->text();
    ERROR_CHECK_BEGIN
    QSharedPointer<UserSql> user = check_auth(login, password);
    open_user_window(user->role(), user->id());
    ERROR_CHECK_END(this)
}

QSharedPointer<UserSql> AuthWindow::check_auth(const QString& login, const QString& password) {
    QSharedPointer<UserSql> user = db::get_user(login);
    if (user && user->password() == User::hash_password(password))
        return user;
    else
        throw std::runtime_error{"Incorrect login or password"};
}

void AuthWindow::on_make_dump_action_triggered()
{
    ERROR_CHECK_BEGIN
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save Database Dump As"), "", tr("SQL files (*.sql)"));
    if (!fileName.isEmpty() && !fileName.isNull()) {
        db::make_dump(fileName);
        show_info("Данные успешно сохранены", false, this);
    }
    ERROR_CHECK_END(this)
}


void AuthWindow::on_load_dump_action_triggered()
{
    ERROR_CHECK_BEGIN
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Database Dump"), "", tr("SQL files (*.sql)"));

    if (!fileName.isEmpty() && !fileName.isNull())
    {
        db::load_dump(fileName);
        show_info("Данные успешно загружены", false, this);
    }
    ERROR_CHECK_END(this)
}


void AuthWindow::on_drop_action_triggered()
{
    if (db::clear_tables()) {
        show_info("Таблицы успешно очищены");
    }
    else {
        show_error("Что-то пошло не так, возможно проблемы с базой данных", this);
    }
}

void AuthWindow::open_user_window(UserRole role, const int& user_id) {
    QWidget* window = nullptr;
    switch(role) {
        case (UserRole::Client): {
            window = new ClientAreaWindow{user_id};
            break;
        }
        case (UserRole::Admin): {
            window = new AdminAreaWindow{user_id};
            break;

        }
        case (UserRole::Worker): {
            window = new WorkerAreaWindow{user_id};
            break;
        }
        case (UserRole::None): {
            throw std::runtime_error{"User role is unknown"};
        }
    }
    ERROR_CHECK_BEGIN
    open_window(window, this);
    ERROR_CHECK_END(this)
}
