#ifndef AVIABLEORDERSLISTWINDOW_H
#define AVIABLEORDERSLISTWINDOW_H

#include <QWidget>
#include "../entities/order.h"
#include <QTableWidgetItem>

namespace Ui {
class AviableOrdersListWindow;
}

class AviableOrdersListWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AviableOrdersListWindow(const int& user_id, QWidget *parent = nullptr);
    ~AviableOrdersListWindow();

private slots:
    void on_take_order_button_clicked();

    void on_about_button_clicked();

    void on_go_area_button_clicked();

    void on_orders_table_widget_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::AviableOrdersListWindow *ui;
    const int mUser_id;
    QVector<OrderSql> mAviable_orders;
};

#endif // AVIABLEORDERSLISTWINDOW_H
