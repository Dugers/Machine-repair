#include <QSettings>
#include <QDir>
#include <QCoreApplication>

#include "config.h"

namespace config {
    namespace db {
    #ifdef QT_DEBUG
        QString config_path = "../../machine/src/config.ini";
    #else
        QString config_path = "config.ini";
    #endif
        QSettings settings(config_path, QSettings::IniFormat);
        QString HOSTNAME = settings.value("db/HOSTNAME").toString();
        QString DBNAME = settings.value("db/DBNAME").toString();
        QString USERNAME = settings.value("db/USERNAME").toString();
        QString PASSWORD = settings.value("db/PASSWORD").toString();
        int PORT = settings.value("db/PORT").toInt();
        QString PASSWORD_SALT = settings.value("db/PASSWORD_SALT").toString();
    }
}
