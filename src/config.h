#ifndef CONFIG
#define CONFIG

#include <QString>

namespace config {
    namespace db {
        extern QString HOSTNAME;
        extern QString DBNAME;
        extern QString USERNAME;
        extern QString PASSWORD;
        extern int PORT;
        extern QString PASSWORD_SALT;
    }
}

#endif
