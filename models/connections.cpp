#include "db.h"
#include <QSqlQuery>
#include "../config.cpp"
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

std::function<const QSqlDatabase&()> db::current_pool = db::PostgresPool::get;
