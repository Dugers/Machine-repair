#ifndef ABOUTORDERWINDOW_H
#define ABOUTORDERWINDOW_H

#include <QWidget>
#include "../entities/order.h"

namespace Ui {
class AboutOrderWindow;
}

class AboutOrderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutOrderWindow(const int& user_id, const int& order_id, QWidget *parent = nullptr);
    ~AboutOrderWindow();
    void hide_description();

private slots:
    void on_about_machine_button_clicked();

    void on_go_area_button_clicked();

private:
    Ui::AboutOrderWindow *ui;
    const int mUser_id;
    const OrderSql mOrder;
};

#endif // ABOUTORDERWINDOW_H
