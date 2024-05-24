#ifndef ADMINAREAWINDOW_H
#define ADMINAREAWINDOW_H

#include <QWidget>
#include "permissioncontroller.h"

namespace Ui {
class AdminAreaWindow;
}

class AdminAreaWindow :
    public QWidget,
    public PermissionController<UserRole::Admin>
{
    Q_OBJECT

public:
    explicit AdminAreaWindow(const int& id, QWidget *parent = nullptr);
    ~AdminAreaWindow();

private slots:
    void on_add_user_button_clicked();

    void on_edit_user_button_clicked();

    void on_exit_button_clicked();

private:
    Ui::AdminAreaWindow *ui;
};

#endif // ADMINAREAWINDOW_H
