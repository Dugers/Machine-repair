#ifndef CLIENTMACHINESWINDOW_H
#define CLIENTMACHINESWINDOW_H

#include <QWidget>

namespace Ui {
class ClientMachinesWindow;
}

class ClientMachinesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientMachinesWindow(const int& user_id, QWidget *parent = nullptr);
    ~ClientMachinesWindow();

private slots:

    void on_add_button_clicked();

    void on_go_area_button_clicked();

private:
    Ui::ClientMachinesWindow *ui;
    const int mUser_id;
};

#endif // CLIENTMACHINESWINDOW_H
