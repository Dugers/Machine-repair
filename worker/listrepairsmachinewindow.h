#ifndef LISTREPAIRSMACHINEWINDOW_H
#define LISTREPAIRSMACHINEWINDOW_H

#include <QWidget>
#include <QTableWidgetItem>
#include "../entities/order.h"

namespace Ui {
class ListRepairsMachineWindow;
}

class ListRepairsMachineWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ListRepairsMachineWindow(const int& user_id, const int& mMachine_id, QWidget *parent = nullptr);
    ~ListRepairsMachineWindow();

private slots:
    void on_about_button_clicked();

    void on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item);

    void on_go_area_button_clicked();

private:
    Ui::ListRepairsMachineWindow *ui;
    const int mUser_id;
    const QVector<OrderSql> mOrders;
};

#endif // LISTREPAIRSMACHINEWINDOW_H
