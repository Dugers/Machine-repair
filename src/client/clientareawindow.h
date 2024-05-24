#ifndef CLIENTAREAWINDOW_H
#define CLIENTAREAWINDOW_H

#include <QWidget>
#include "permissioncontroller.h"

namespace Ui {
class ClientAreaWindow;
}

class ClientAreaWindow :
    public QWidget,
    public PermissionController<UserRole::Client>
{
    Q_OBJECT

public:
    explicit ClientAreaWindow(const int& user_id, QWidget *parent = nullptr);
    ~ClientAreaWindow();

private slots:
    void on_list_services_button_clicked();

    void on_my_machines_button_clicked();

    void on_exit_button_clicked();

private:
    Ui::ClientAreaWindow *ui;
};

#endif // CLIENTAREAWINDOW_H
