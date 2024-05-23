#include "db.h"
#include <QSqlQuery>
#include "config.h"
#include <QProcess>
#include <QSqlRecord>

const QSqlDatabase& db::PostgresPool::get() {
    static QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    if (!db.isOpen()) {
        // Установка параметров подключения
        db.setHostName(config::db::HOSTNAME);   // Адрес сервера баз данных
        db.setDatabaseName(config::db::DBNAME);    // Название базы данных
        db.setUserName(config::db::USERNAME);  // Имя пользователя
        db.setPassword(config::db::PASSWORD);  // Пароль пользователя
        db.setPort(config::db::PORT);              // Порт (стандартный для PostgreSQL - 5432)
        // Попытка открыть соединение с базой данных
        if (!db.open())
            throw std::runtime_error("Couldn't open the DB");
    }
    return db;
}
void db::PostgresPool::load_dump(const QString& filename) {
    if (!db::drop_tables())
        throw std::runtime_error{"Не удалось удалить старые таблицы"};
    QStringList args;
    args << "-h";
    args << config::db::HOSTNAME;
    args << "-p";
    args << QString::number(config::db::PORT);
    args << "-U";
    args << config::db::USERNAME;
    args << "-d";
    args << config::db::DBNAME;
    args << "-f";
    args << filename;

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
}

void db::PostgresPool::make_dump(const QString& filename) {
    QStringList args;
    args << "-h";
    args << config::db::HOSTNAME;
    args << "-p";
    args << QString::number(config::db::PORT);
    args << "-U";
    args << config::db::USERNAME;
    args << "-F";
    args << "p"; // формат plain-text SQL
    args << "-f"; // сохранить в файл
    args << filename; // путь к файлу, куда будет сохранен дамп
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
}

const std::function<const QSqlDatabase&()> db::current_pool = db::PostgresPool::get;
const std::function<void(const QString&)> db::load_dump = db::PostgresPool::load_dump;
const std::function<void(const QString&)> db::make_dump = db::PostgresPool::make_dump;
