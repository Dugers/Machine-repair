#ifndef ABOUTMACHINEWINDOW_H
#define ABOUTMACHINEWINDOW_H

#include <QWidget>
#include "permissioncontroller.h"

namespace Ui {
class AboutMachineWindow;
}

class AboutMachineWindow :
    public QWidget,
    public PermissionController<UserRole::Worker>
{
    Q_OBJECT

public:
    explicit AboutMachineWindow(const int& user_id, const int& machine_id, QWidget *parent = nullptr);
    ~AboutMachineWindow();

private slots:
    void on_order_button_clicked();

    void on_go_area_button_clicked();

private:
    Ui::AboutMachineWindow *ui;
    const int mMachine_id;
};

#endif // ABOUTMACHINEWINDOW_H
