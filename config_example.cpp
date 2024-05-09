// remove this file to config.cpp

#include <QString>
#include <QDateTime>

#ifndef CONFIG
#define CONFIG

namespace config {
    namespace db {
        const QString HOSTNAME = "localhost";   // Адрес сервера баз данных
        const QString DBNAME = "machines";    // Название базы данных
        const QString USERNAME = "postgres";  // Имя пользователя
        const QString PASSWORD = "password";  // Пароль пользователя
        const int PORT = 5432;
        const QString PASSWORD_SALT = "RANDOM_SYMBOLS";
    }
}
#endif
