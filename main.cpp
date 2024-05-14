#include "authwindow.h"
#include "worker/aboutorderwindow.h"
#include "models/db.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    db::create_tables();
    AuthWindow w;
    w.show();
    return a.exec();
}
