#include "edituserwindow.h"
#include "tools/messages.h"
#include "ui_edituserwindow.h"
#include "adminareawindow.h"
#include "../models/db.h"
#include "adduserwindow.h"
#include <QMessageBox>
#include "authwindow.h"

EditUserWindow::EditUserWindow(const int& user_id, const int& edited_user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUserWindow),
    mUser_id{user_id},
    mEdited_user{db::get_user(edited_user_id)}
{
    if (!mEdited_user)
        throw std::runtime_error{"Ошибка при получение данных о пользователе"};
    ui->setupUi(this);
    ui->user_login_line_edit->setText(mEdited_user->login());
    ui->user_name_line_edit->setText(mEdited_user->name());
    const auto roles = get_user_roles();
    int role_index = -1;
    for (int i = 0; i < roles.size(); ++i) {
        ui->user_role_combo_box->addItem(roles[i].first);
        if (roles[i].second == mEdited_user->role())
            role_index = i;
    }
    if (role_index == -1)
        throw std::runtime_error{"Пользователь имеет неизвестную роль"};
    ui->user_role_combo_box->setCurrentIndex(role_index);
}

EditUserWindow::~EditUserWindow()
{
    delete ui;
}

void EditUserWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AdminAreaWindow{mUser_id}, this);
    ERROR_CHECK_END(this)
}


void EditUserWindow::on_add_button_clicked()
{
    ERROR_CHECK_BEGIN
    validate();
    const QString name = ui->user_name_line_edit->text().simplified();
    const QString login = ui->user_login_line_edit->text().simplified();
    const QString password = ui->user_password_line_edit->text().simplified();
    const UserRole role = role_by_str(ui->user_role_combo_box->currentText());
    validate(name, login, password, role);
    update(name, login, password, role);
    show_info("Данные пользователя успешно обновленны", false, this);
    ERROR_CHECK_END(this)
}

void EditUserWindow::validate() {
    if (this->ui->user_name_line_edit->text().isEmpty())
        throw std::runtime_error{"Введите имя"};
    if (this->ui->user_role_combo_box->currentIndex() == -1)
        throw std::runtime_error{"Выберите роль"};
}

void EditUserWindow::validate(const QString& name, const QString& login, const QString& password, const UserRole& role) {
    if (name != mEdited_user->name())
        User::validate_name(name);
    if (login != mEdited_user->login())
        User::validate_login(login);
    if (role != mEdited_user->role())
        User::validate_role(role);
    if (!password.isEmpty())
        User::validate_password(password);
}

bool EditUserWindow::check_changes(const QString& name, const QString& login, const QString& password, const UserRole& role){
    if (name == mEdited_user->name() && login == mEdited_user->login() &&
            (role == mEdited_user->role()) && password.isEmpty())
    {
        show_info("Изменений не было", false, this);
        return false;
    }
    return true;
}

void EditUserWindow::update(const QString& name, const QString& login, const QString& password, const UserRole& role) {
    if (name != mEdited_user->name() && !db::update_user_name(mEdited_user->id(), name))
        throw std::runtime_error{"Не удалось обновить имя"};
    if (login != mEdited_user->login() && !db::update_user_login(mEdited_user->id(), login))
        throw std::runtime_error{"Не удалось обновить логин"};
    if (role != mEdited_user->role() && !db::update_user_role(mEdited_user->id(), role))
        throw std::runtime_error{"Не удалось обновить роль"};
    if (!password.isEmpty() && !db::update_user_password(mEdited_user->id(), password))
        throw std::runtime_error{"Не удалось обновить пароль"};
}
