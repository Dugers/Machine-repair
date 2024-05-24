#include "adduserwindow.h"
#include "tools/messages.h"
#include "tools/text.h"
#include "ui_adduserwindow.h"
#include "adminareawindow.h"
#include "../models/db.h"
#include "../entities/user.h"
#include <QMessageBox>
#include "authwindow.h"

AddUserWindow::AddUserWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    PermissionController<UserRole::Admin>{user_id},
    ui(new Ui::AddUserWindow)
{
    ui->setupUi(this);
    const QVector<QPair<QString, UserRole>>& roles = get_user_roles();
    for (auto const& role: roles)
        this->ui->user_role_combo_box->addItem(role.first);
}

AddUserWindow::~AddUserWindow()
{
    delete ui;
}

void AddUserWindow::on_go_area_button_clicked()
{
    ERROR_CHECK_BEGIN
    open_window(new AdminAreaWindow{user_id()}, this);
    ERROR_CHECK_END(this)
}


void AddUserWindow::on_add_button_clicked()
{
    ERROR_CHECK_BEGIN
    confirm();
    validate();
    const User user = prepare_data();
    if (!db::create_user(user))
        throw std::runtime_error{"Не удалось создать пользователя, возможно:\n1) Проблемы с базой данных\n2) Пользователь с таким логином уже существует"};
    show_info("Успешно создан пользователь\nЛогин: " + user.login() + "\nПароль: " + user.password(), false, this);
    ERROR_CHECK_END(this)
}

QString AddUserWindow::generate_login(QString name) {
    User::validate_name(name);
    name = name.replace(' ', '_').toLower();
    translit(name);
    QSharedPointer<UserSql> user = db::get_user(name);
    int add_index = 0;
    while (user) {
        ++add_index;
        user = db::get_user(name + QString::number(add_index));
    }
    if (add_index != 0)
        name += QString::number(add_index);
    return name;
}

void AddUserWindow::validate() {
    if (this->ui->user_name_line_edit->text().isEmpty())
        throw std::runtime_error{"Введите имя"};
    if (this->ui->user_role_combo_box->currentIndex() == -1)
        throw std::runtime_error{"Выберите роль"};
}

void AddUserWindow::validate(const QString& name, const QString& login, const QString& password, const QString& role) {
    User::validate_name(name);
    if (login.size())
        User::validate_login(login);
    if (password.size())
        User::validate_password(password);
    User::validate_role(role);
}

User AddUserWindow::prepare_data() {
    const QString name = this->ui->user_name_line_edit->text().simplified();
    QString login = this->ui->user_login_line_edit->text().simplified();
    QString password = this->ui->user_password_line_edit->text().simplified();
    const QString role = this->ui->user_role_combo_box->currentText();
    validate(name, login, password, role);
    if (login.isEmpty())
        login = generate_login(name);
    if (password.isEmpty())
        password = User::generate_password();
    return {std::move(name), std::move(login), std::move(password), role_by_str(role)};
}
