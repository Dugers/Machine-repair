#include "edituserwindow.h"
#include "ui_edituserwindow.h"
#include "adminareawindow.h"
#include "../models/db.h"
#include "adduserwindow.h"
#include <QMessageBox>

EditUserWindow::EditUserWindow(const int& user_id, const QString& edited_user_login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUserWindow),
    mUser_id{user_id},
    mEdited_user{db::get_user(db::PostgresPool::get(), edited_user_login)}
{
    if (!mEdited_user)
        throw std::runtime_error{"Ошибка при получение данных о пользователе"};
    ui->setupUi(this);
    ui->user_login_line_edit->setText(mEdited_user->second.login());
    ui->user_name_line_edit->setText(mEdited_user->second.name());
    auto roles = get_user_roles();
    int role_index = -1;
    for (int i = 0; i < roles.size(); ++i) {
        ui->user_role_combo_box->addItem(roles[i].first);
        if (roles[i].second == mEdited_user->second.role())
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
    (new AdminAreaWindow{mUser_id})->show();
    this->close();
}


void EditUserWindow::on_add_button_clicked()
{
    QMessageBox msgBox{this};
    QString name = ui->user_name_line_edit->text().simplified();
    QString login = ui->user_login_line_edit->text().simplified();
    QString password = ui->user_password_line_edit->text().simplified();
    UserRole role = role_by_str(ui->user_role_combo_box->currentText());
    if (name == mEdited_user->second.name() && login == mEdited_user->second.login() &&
            role == mEdited_user->second.role() && password.isEmpty())
    {
        msgBox.setText("Изменений не было");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        return;
    }
    try {
        if (name != mEdited_user->second.name())
            AddUserWindow::validate_name(name);
        if (login != mEdited_user->second.login())
            AddUserWindow::validate_login(login);
        if (role != mEdited_user->second.role())
            AddUserWindow::validate_role(mEdited_user->second.role());
        if (!password.isEmpty()) {
            AddUserWindow::validate_password(password);
        }
        if (name != mEdited_user->second.name() && !db::update_user_name(db::PostgresPool::get(), mEdited_user->first, name))
            throw std::runtime_error{"Не удалось обновить имя"};
        if (login != mEdited_user->second.login() && !db::update_user_login(db::PostgresPool::get(), mEdited_user->first, login))
            throw std::runtime_error{"Не удалось обновить логин"};
        if (role != mEdited_user->second.role() && !db::update_user_role(db::PostgresPool::get(), mEdited_user->first, role))
            throw std::runtime_error{"Не удалось обновить роль"};
        if (!password.isEmpty() && !db::update_user_password(db::PostgresPool::get(), mEdited_user->first, password))
            throw std::runtime_error{"Не удалось обновить пароль"};
        msgBox.setText("Данные пользователя успешно обновленны");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
    catch (std::exception& e) {
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

}

