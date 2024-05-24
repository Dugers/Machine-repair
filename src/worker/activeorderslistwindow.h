#ifndef ACTIVEORDERSLISTWINDOW_H
#define ACTIVEORDERSLISTWINDOW_H

#include <QWidget>
#include <QTableWidgetItem>
#include "../entities/order.h"
#include "permissioncontroller.h"

namespace Ui {
class ActiveOrdersListWindow;
}

class ActiveOrdersListWindow :
    public QWidget,
    public PermissionController<UserRole::Worker>
{
    Q_OBJECT

public:
    explicit ActiveOrdersListWindow(const int& user_id, QWidget *parent = nullptr);
    ~ActiveOrdersListWindow();

private slots:
    void on_about_button_clicked();

    void on_complete_order_button_clicked();

    void on_go_area_button_clicked();

    void on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::ActiveOrdersListWindow *ui;
    QVector<OrderSql> mActive_orders;
};

#endif // ACTIVEORDERSLISTWINDOW_H
