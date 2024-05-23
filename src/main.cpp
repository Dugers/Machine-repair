#include "authwindow.h"
#include "models/db.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    db::create_tables();
    AuthWindow w;
    w.show();
    return a.exec();
}
