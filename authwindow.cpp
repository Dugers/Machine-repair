#include <QMessageBox>
#include <QProcess>
#include <QFileDialog>
#include "authwindow.h"
#include "ui_authwindow.h"
#include "models/db.h"
#include "client/clientareawindow.h"
#include "admin/adminareawindow.h"
#include "worker/workerareawindow.h"
#include "config.cpp"

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
    try {
        QSharedPointer<QPair<int, User>> user = check_auth(login, password);
        switch(user->second.role()) {
            case (UserRole::Client): {
                ClientAreaWindow* client = new ClientAreaWindow{user->first};
                client->show();
                break;
            }
            case (UserRole::Admin): {
                AdminAreaWindow* admin = new AdminAreaWindow{user->first};
                admin->show();
                break;
            }
            case (UserRole::Worker): {
                WorkerAreaWindow* worker = new WorkerAreaWindow{user->first};
                worker->show();
                break;
            }
            case (UserRole::None): {
                throw std::runtime_error{"User role is unknown"};
                break;
            }
        }
        this->close();
    }

    catch (std::exception& e) {
        QMessageBox msgBox{this};
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}

QSharedPointer<QPair<int, User>> AuthWindow::check_auth(const QString& login, const QString& password) {
    QSharedPointer<QPair<int, User>> user = db::get_user(db::PostgresPool::get(), login);
    if (user && user->second.password() == User::hash_password(password))
        return user;
    else
        throw std::runtime_error{"Incorrect login or password"};
}

void AuthWindow::on_make_dump_action_triggered()
{
    QMessageBox msgBox{this};
    try {
        QString fileName = QFileDialog::getSaveFileName(
            this, tr("Save Database Dump As"), "", tr("SQL files (*.sql)"));
        if (!fileName.isEmpty() && !fileName.isNull()) {
            QStringList args;
            args << "-U";
            args << config::db::USERNAME;
            args << "-F";
            args << "p"; // формат plain-text SQL
            args << "-f"; // сохранить в файл
            args << fileName; // путь к файлу, куда будет сохранен дамп
            args << config::db::DBNAME;

            QProcess dumpProcess;

            // Устанавливаем переменные среды для процесса
            QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
            env.insert("PGPASSWORD", config::db::PASSWORD); // добавляем пароль
            dumpProcess.setProcessEnvironment(env);

            dumpProcess.start("pg_dump", args);
            dumpProcess.waitForFinished(-1);

            if (dumpProcess.exitCode() != 0) {
                // Ошибка во время выполнения команды
                throw std::runtime_error{dumpProcess.readAllStandardError()};
            }
            msgBox.setText("Данные успешно сохранены");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }
    }
    catch (std::exception& e) {
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}


void AuthWindow::on_load_dump_action_triggered()
{
    QMessageBox msgBox{this};
    try{
        QString fileName = QFileDialog::getOpenFileName(
            this, tr("Open Database Dump"), "", tr("SQL files (*.sql)"));

        if (!fileName.isEmpty() && !fileName.isNull())
        {
            if (!db::drop_tables(db::PostgresPool::get()))
                throw std::runtime_error{"Не удалось удалить старые таблицы"};
            QStringList args;
            args << "-U";
            args << config::db::USERNAME;
            args << "-d";
            args << config::db::DBNAME;
            args << "-f";
            args << fileName;

            // Создаем новый процесс
            QProcess loadProcess;

            // Устанавливаем переменные среды для процесса
            QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
            env.insert("PGPASSWORD", config::db::PASSWORD); // добавляем пароль
            loadProcess.setProcessEnvironment(env);

            loadProcess.start("psql", args);
            loadProcess.waitForFinished(-1);

            if (loadProcess.exitCode() != 0)
            {
                // Ошибка во время выполнения команды
                throw std::runtime_error{loadProcess.readAllStandardError()};
            }
            msgBox.setText("Данные успешно загружены");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }
    }
    catch (std::exception& e) {
        msgBox.setText(e.what());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}


void AuthWindow::on_drop_action_triggered()
{
    QMessageBox msgBox{this};
    if (db::clear_tables(db::PostgresPool::get())) {
        msgBox.setText("Таблицы успешно очищены");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
    else {
        msgBox.setText("Что-то пошло не так, возможно проблемы с базой данных");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}
