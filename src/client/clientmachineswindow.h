#ifndef CLIENTMACHINESWINDOW_H
#define CLIENTMACHINESWINDOW_H

#include <QWidget>
#include "permissioncontroller.h"
#include <QTableWidgetItem>

namespace Ui {
class ClientMachinesWindow;
}

class ClientMachinesWindow :
    public QWidget,
    public PermissionController<UserRole::Client>
{
    Q_OBJECT

public:
    explicit ClientMachinesWindow(const int& user_id, QWidget *parent = nullptr);
    ~ClientMachinesWindow();

private slots:

    void on_add_button_clicked();

    void on_go_area_button_clicked();

private:
    Ui::ClientMachinesWindow *ui;
};

#endif // CLIENTMACHINESWINDOW_H
