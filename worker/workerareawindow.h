#ifndef WORKERAREAWINDOW_H
#define WORKERAREAWINDOW_H

#include <QWidget>

namespace Ui {
class WorkerAreaWindow;
}

class WorkerAreaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerAreaWindow(const int& user_id, QWidget *parent = nullptr);
    ~WorkerAreaWindow();

private slots:
    void on_aviable_orders_list_button_clicked();

    void on_active_orders_list_button_clicked();

    void on_exit_button_clicked();

private:
    Ui::WorkerAreaWindow *ui;
    const int mUser_id;
};

#endif // WORKERAREAWINDOW_H
