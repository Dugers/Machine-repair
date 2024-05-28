#include "authwindow.h"
#include "models/db.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {db::create_tables();} catch(...) {}
    AuthWindow w;
    w.show();
    return a.exec();
}
