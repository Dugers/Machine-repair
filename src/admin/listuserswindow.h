#ifndef LISTUSERSWINDOW_H
#define LISTUSERSWINDOW_H

#include <QWidget>
#include <QTableWidgetItem>
#include "entities/user.h"
#include "permissioncontroller.h"

namespace Ui {
class ListUsersWindow;
}

class ListUsersWindow :
    public QWidget,
    public PermissionController<UserRole::Admin>
{
    Q_OBJECT

public:
    explicit ListUsersWindow(const int& user_id, QWidget *parent = nullptr);
    int get_selected_user_id() const;
    ~ListUsersWindow();

private slots:
    void on_go_area_button_clicked();

    void on_delete_button_clicked();

    void on_edit_button_clicked();

    void on_users_table_widget_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::ListUsersWindow *ui;
    const int USER_LOGIN_COLUMN = 1;
};

#endif // LISTUSERSWINDOW_H
