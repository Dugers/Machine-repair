#include "adduserwindow.h"
#include "ui_adduserwindow.h"
#include "adminareawindow.h"
#include "../models/db.h"
#include "../entities/user.h"
#include <QMessageBox>
#include <unordered_map>
#include <random>

AddUserWindow::AddUserWindow(const int& user_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddUserWindow),
    mUser_id{user_id}
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
    (new AdminAreaWindow{mUser_id})->show();
    this->close();
}


void AddUserWindow::on_add_button_clicked()
{

    try {
        if (this->ui->user_name_line_edit->text().isEmpty())
            throw std::runtime_error{"Введите имя"};
        if (this->ui->user_role_combo_box->currentIndex() == -1)
            throw std::runtime_error{"Выберите роль"};
        QString name = this->ui->user_name_line_edit->text().simplified();
        QString login = this->ui->user_login_line_edit->text().simplified();
        QString password = this->ui->user_password_line_edit->text().simplified();
        QString role = this->ui->user_role_combo_box->currentText();
        this->validate(name, login, password, role);
        if (login.isEmpty())
            login = this->generate_login(name);
        if (password.isEmpty())
            password = this->generate_password();
        User user{std::move(name), std::move(login), std::move(password), role_by_str(role)};
        if (!db::create_user(user))
            throw std::runtime_error{"Не удалось создать пользователя, возможно:\n1) Проблемы с базой данных\n2) Пользователь с таким логином уже существует"};
        QMessageBox msgBox{this};
        msgBox.setText("Успешно создан пользователь\nЛогин: " + user.login() + "\nПароль: " + user.password());
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
    catch (std::exception e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
}

QString AddUserWindow::generate_login(QString name) {
    AddUserWindow::validate_name(name);
    name = name.replace(' ', '_').toLower();
    translit(name);
    QSharedPointer<QPair<int, User>> user = db::get_user(name);
    int add_index = 0;
    while (user) {
        ++add_index;
        user = db::get_user(name + QString::number(add_index));
        qDebug() << name + QString::number(add_index);
    }
    if (add_index != 0)
        name += QString::number(add_index);
    return name;
}
QString AddUserWindow::generate_password() {
    std::mt19937 random_symbols{std::random_device{}()};
    static const QString symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[]{}|;:,.<>?/";
    QString password;
    for (int i = 0; i < 32; ++i) {
        password.push_back(symbols[random_symbols()%symbols.size()]);
    }
    return password;
}

void AddUserWindow::translit(QString& string) {
    static const std::unordered_map<QString, QString> replaced_chars = {
        {"й", "j"},
        {"ц", "c"},
        {"у", "u"},
        {"к", "k"},
        {"е", "e"},
        {"н", "n"},
        {"г", "g"},
        {"ш", "sh"},
        {"щ", "shch"},
        {"з", "z"},
        {"ъ", "ie"},
        {"ф", "f"},
        {"ы", "y"},
        {"в", "v"},
        {"а", "a"},
        {"п", "p"},
        {"р", "r"},
        {"о", "o"},
        {"л", "l"},
        {"д", "d"},
        {"ж", "zh"},
        {"э", "e"},
        {"я", "ya"},
        {"ч", "ch"},
        {"с", "s"},
        {"м", "m"},
        {"и", "i"},
        {"т", "t"},
        {"ь", "io"},
        {"б", "b"},
        {"ю", "yu"},
        {"ё", "yo"},
        {"х", "h"}
    };
    for (auto const& replaced_char : replaced_chars) {
        string = string.replace(replaced_char.first, replaced_char.second);
    }
}

void AddUserWindow::validate(const QString& name, const QString& login, const QString& password, const QString& role) {
    validate_name(name);
    if (login.size())
        validate_login(login);
    if (password.size())
        validate_password(password);
    validate_role(role);
}

void AddUserWindow::validate_name(const QString& name) {
    if (name != name.simplified())
        throw std::runtime_error{"the name contains extra spaces"};
    if (name.size() < 6)
        throw std::runtime_error{"the name is too short (need >= 6 chars)"};
    static const QString allowed_characters = "йцукенгшщзфывапролджэячсмитьбюёЙЦУКЕНГШЩЗФЫВАПРОЛДЖЭЯЧСМИТЬБЮqwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ";
    for (auto const& ch : name) {
        if (!allowed_characters.contains(ch))
            throw std::runtime_error{"You can only use letters and spaces"};
    }
}

void AddUserWindow::validate_login(const QString& login) {
    if (login.size() < 6)
        throw std::runtime_error{"the login is too short (need >= 6 chars)"};
    static const QString allowed_characters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_";
    for (auto const& ch : login) {
        if (!allowed_characters.contains(ch))
            throw std::runtime_error{"You can only use Latin letters and underscore"};
    }
}

void AddUserWindow::validate_password(const QString& password) {
    if (password.size() < 6)
        throw std::runtime_error{"the password is too short (need >= 6 chars)"};
}

void AddUserWindow::validate_role(const QString& role) {
    if (role_by_str(role) == UserRole::None)
        throw std::runtime_error{"Unknown role"};
}

void AddUserWindow::validate_role(const UserRole& role) {
    if (role == UserRole::None)
        throw std::runtime_error{"Unknown role"};
}
