#ifndef LISTUSERSWINDOW_H
#define LISTUSERSWINDOW_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class ListUsersWindow;
}

class ListUsersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ListUsersWindow(const int& user_id, QWidget *parent = nullptr);
    ~ListUsersWindow();

private slots:
    void on_go_area_button_clicked();

    void on_delete_button_clicked();

    void on_edit_button_clicked();

    void on_users_table_widget_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::ListUsersWindow *ui;
    const int mUser_id;
};

#endif // LISTUSERSWINDOW_H
