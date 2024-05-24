#ifndef ADDMACHINEWINDOW_H
#define ADDMACHINEWINDOW_H

#include <QWidget>
#include "permissioncontroller.h"

namespace Ui {
class AddMachineWindow;
}

class AddMachineWindow :
    public QWidget,
    public PermissionController<UserRole::Client>
{
    Q_OBJECT

public:
    explicit AddMachineWindow(const int& user_id, QWidget *parent = nullptr);
    ~AddMachineWindow();
    void validate(const QString& name, const int& type_id, const int& brand_id);

private slots:
    void on_add_button_clicked();

    void on_type_combo_box_currentIndexChanged(int index);

    void on_go_area_button_clicked();

    void on_brand_combo_box_currentIndexChanged(int index);

private:
    Ui::AddMachineWindow *ui;
};

#endif // ADDMACHINEWINDOW_H
