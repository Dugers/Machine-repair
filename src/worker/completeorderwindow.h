#ifndef COMPLETEORDERWINDOW_H
#define COMPLETEORDERWINDOW_H

#include <QWidget>
#include "../entities/order.h"
#include "permissioncontroller.h"

namespace Ui {
class CompleteOrderWindow;
}

class CompleteOrderWindow :
    public QWidget,
    public PermissionController<UserRole::Worker>
{
    Q_OBJECT

public:
    explicit CompleteOrderWindow(const int& user_id, const int& order_id, QWidget *parent = nullptr);
    ~CompleteOrderWindow();
    static void validate_description(const QString& description);
    void confirm() override;

private slots:
    void on_complete_order_button_clicked();

    void on_go_area_button_clicked();

private:
    Ui::CompleteOrderWindow *ui;
    const int mOrder_id;
};

#endif // COMPLETEORDERWINDOW_H
